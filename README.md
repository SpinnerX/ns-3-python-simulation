# ns-3-python-simulation

This is a basic NS-3 python simulation that is used to demonstrate basic signal transmission.

# Getting Started

Make sure to already have `python` and `pip` (`pipx`) already installed.

## Installing ns3 to run

First clone the repository and configure ns3:

```bash
git clone https://github.com/nsnam/ns-3-dev.git
cd ns-3-dev

# Configuring
./ns3 configure --enable-python-bindings --enable-examples
./ns3
```

## Clone this project

To run this simulation for ease of demonstration, you can just clone this project into the ns3 project.


## Running the Project

To run specific python simulation files.

Here is how to run:

```
./ns3 run <filename>
```

I added a test file called `test.py` to make sure it is working fine.

To run, do the following:

```
./ns3 run test.py
```


