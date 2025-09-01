#include "server.h"

#include <controller/CartController.h>

#include <service/CartService.h>

#include "listener.h"
#include "router.h"

namespace server_detail {
class Impl {
public:
  explicit Impl(int concurrency) : ioc(concurrency) {

    router.to<CartController, &CartController::ViewCart>(
        R"(/cart/view/([a-zA-Z0-9_-]+))", cart_service_);
    router.to<CartController, &CartController::AddProductToCart>(
        R"(/cart/product)", cart_service_);
  }

  void launch(const char *address, unsigned short port) {
    using tcp = boost::asio::ip::tcp;
    auto endpoint = tcp::endpoint{boost::asio::ip::make_address(address), port};
    std::make_shared<Listener>(ioc, endpoint, handler)->run();
  }

  void run() { ioc.run(); }

  void stop() { ioc.stop(); }

private:
  boost::asio::io_context ioc;

  UserService user_service_{};
  ProductService product_service_{};
  CartService cart_service_{user_service_, product_service_};

  Router router;
  std::function<http::response<http::string_body>(
      const http::request<http::string_body> &)>
      handler = router.handler();
};
} // namespace server_detail

Server::Server(int concurrency)
    : impl(std::make_unique<server_detail::Impl>(concurrency)),
      concurrency(concurrency) {}

Server::~Server() {
  impl->stop();
  for (auto &worker : threads) {
    if (worker.joinable()) {
      worker.join();
    }
  }
}

void Server::run(const char *address, unsigned short port) {
  impl->launch(address, port);
  threads.reserve(concurrency);
  for (auto i = concurrency; i > 0; --i) {
    threads.emplace_back([this] { impl->run(); });
  }
}
