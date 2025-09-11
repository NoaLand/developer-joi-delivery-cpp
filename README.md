# Welcome to JOI Delivery
JOI Delivery is built for real life. For the young professional who gets home late and doesn’t have the energy to cook. For the student with an exam tomorrow and an empty fridge tonight. These aren’t exceptions — they’re everyday moments. That’s why JOI Delivery brings food and groceries to your door, fast, fresh, and right when you need them.

Customers struggle with:

- Cluttered browsing experiences that don’t understand their preferences.
- Limited customization when ordering meals or groceries.
- Unclear order status or delivery timelines.
- Poor payment experience, or failed checkouts.
- Lack of timely feedback channels to report a bad experience or appreciate a good one.

JOI Delivery was built not just as another delivery app, but as a thoughtful, technology-first platform that reimagines how essentials reach customers in the most seamless way.

# Introducing JOI Delivery

JOI Delivery, launched in 2024, is a hyperlocal delivery app designed to bring food and groceries to your doorstep in under 45 minutes. With the tagline "Speed meets convenience," it connects customers to nearby restaurants and stores through a seamless digital experience. The app solves the hassle of long wait times and limited local options by offering real-time tracking, instant order updates, and a wide network of trusted vendors.

## Business Goals
- Differentiated Value Proposition & Niche Dominance
- Deliver Unmatched Customer Experience & Loyalty
- Superior Operational Efficiency & Cost Advantage
- Robust & Engaged Partner Ecosystem

## Why they need Thoughtworks help
As JOI Delivery continues to grow and serve more neighborhoods, we’re scaling our platform to handle increasing demand, enhance user experience, and support smarter delivery logistics. They're looking for passionate developers to help us build robust, efficient, and scalable solutions that power everything from order placement to real-time tracking.
Your expertise will directly impact how quickly and reliably customers receive their essentials—and how smoothly local vendors and delivery partners operate within our ecosystem.

### Users/Customers
Sample user profiles are available in the repository to support development and testing scenarios.

| UserId   | FirstName | LastName|
|----------|-----------|---------|
| user101  | John      | Doe     |

### Stores
Sample store data seeded for development purposes only.

| StoreId  | OutletName     |
|----------|----------------|
| store101 | Fresh Picks    |
| store102 | Natural Choice |

### Grocery Products
Dummy Products for Stores to sell and users to buy from.

| ProductId  | ProductName | StoreRefId |
|------------|-------------|------------|
| product101 | Wheat Bread | store101   |
| product102 | Spinach     | store101   |
| product103 | Crackers    | store101   |

## Tech Requirements
To build the project, one need to meet the below set of techical stack requirements.

1. CMake 3.23 above is **required**.

Check [here](https://cmake.org/download/) for installation if you get a older version.

2. Conan 2.0 above is **required**.

Check [here](https://docs.conan.io/2/installation.html) for installation if you get a older version.

The project makes use of Conan to help you out carrying some common tasks such as building the project or running it.

Technically, Conan is not must have, but in order to simplify environment setup, following guideline is based on Conan.

### Build the project

0. Setup a profile for Conan, if this is the first time you get Conan 2.x run on your machine.

```shell
conan profile detect
```

Now, assuming you are already at the root of this repository, follow:

1. Install or build the dependencies

```shell
conan install . --output-folder=build -s build_type=Debug --build=missing
```

2. Generate build system for this repository

```shell
cmake --preset conan-debug
```

> ☀️ If you are building on **Windows with Visual Studio** (Generator), please use `conan-default` instead of, like:
>
> ```shell
> cmake --preset conan-default
> ```

3. Build this repository

```shell
mkdir -p build
cd build
cmake ..
make
```

> ☀️ If you are building on **Windows with Visual Studio** (Generator), and prefer IDE, you could find a generate project file in `build` directory and open it with Visual Studio for building and test running.

> ⚡️With option `-j<number>` (e.g. -j4 ) could enable parallel build job, which could usually accelerate your build.

### Run the tests

Unit tests can be executed as follows.

- Run unit tests only

  ```shell
  $ ctest .
  ```

### Run the application
  ```shell
  $ ./app
  ```

Below are the outputs from execution of 
```
./app
``` 

#### Sample Execution Output 01:
```
Grocery Store Management CLI
1. Add product to Cart for a user
2. To View Cart of a specific user
3. Exit
Select an option (1-3): 1
Adding product to Cart for a user
Enter User ID: user101
Enter Product ID: product101
Enter Outlet ID: store101
{
    "add": {
        "cart": {
            "cartId": "cart101",
            "outlet": {
                "outletId": "store101",
                "outletName": "Fresh Picks"
            },
            "products": [
                {
                    "mrp": 10.5,
                    "productId": "product101",
                    "productName": "Wheat Bread"
                }
            ]
        },
        "proudct": {
            "mrp": 10.5,
            "productId": "product101",
            "productName": "Wheat Bread"
        },
        "sellingPrice": 1.5725600291792398e+25
    }
}
```

 #### Sample Execution Output 02:
 ```
 Grocery Store Management CLI
1. Add product to Cart for a user
2. To View Cart of a specific user
3. Exit
Select an option (1-3): 2
Viewing cart of a specific user...
Enter User ID: user102
User ID: user102
-- view query - user id user102
{
    "view": {
        "cartId": "cart102",
        "outlet": {
            "outletId": "store101",
            "outletName": "Fresh Picks"
        },
        "products": []
    }
}
```

#### Sample Execution Output 03:
```
Grocery Store Management CLI
1. Add product to Cart for a user
2. To View Cart of a specific user
3. Exit
Select an option (1-3): 3
Exiting the application...
```
