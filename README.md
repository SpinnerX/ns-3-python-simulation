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

# Building ns3
./ns3 build
```

## Clone this project

To run this simulation for ease of demonstration, you can just clone this project into the ns3 project.

Still inside `ns-3-dev` directory. Clone this project itself by doing:

```
git clone https://github.com/SpinnerX/ns-3-python-simulation scratch/ns-3-python-simulation
```

## Building the Project

To demonstrate if the setup builds correctly, we are going to build the `ns-demo.cc` file. 

> [!TIP]
> every code in the `scratch/` directory can be compiled simply doing `./ns3 build <file or directory>`

Here is how to run:

```
./ns3 build scratch/ns-3-python-simulation/ns-demo
```


## Running the Project

To execute the ns3 simulation, is is similar to compiling the simulation.

Here is to running `ns-demo.cc`

```
./ns3 run scratch/ns-3-python-simulation/ns-demo
```
