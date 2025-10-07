# NPC Simulation

An AI NPC simulation developed in Unreal Engine that facilitates emergent gameplay. The system uses a needs-based, reactive approach, built with C++ and Unreal's State Trees to create a dynamic world with unscripted gameplay opportunities.

[![Showcase Video](https://img.youtube.com/vi/v6w6LgyzEj0/0.jpg)](https://youtu.be/v6w6LgyzEj0)

> [!IMPORTANT]
> This repository contains only the source code for the project. The `Content` folder, has been intentionally excluded to respect third-party asset licenses. As a
      result, this project **cannot be built or run** from this repository alone. Its purpose is to showcase the underlying C++ code
      and AI architecture. If you are interested in seeing the full project feel free to contact me.

## The Code

All source code for this project is located in the [`Source/`](Source/) directory, which contains two modules:

- [`NPCEnvironment_Demo/`](Source/NPCEnvironment_Demo/): Contains the main project source.
  - [`NPC/`](Source/NPCEnvironment_Demo/NPC/): The AI NPC
  - [`Inventory/`](Source/NPCEnvironment_Demo/Inventory/): The inventory system including state tree tasks and conditions
- [`CustomStateTree/`](Source/CustomStateTree/): Generic State Tree tasks and conditions

## State Trees

The core of the NPC logic is defined in a [State Trees](https://dev.epicgames.com/documentation/en-us/unreal-engine/state-tree-in-unreal-engine). Below are screenshots of its structure, which outline the NPC's decision-making process.

![NPC State Tree](Images/state-tree_NPC.png)

Additionally, Smart Objects  have their own State Trees such as the water source and item State Trees shown below.

![Water Source State Tree](Images/state-tree_water-source.png)

![Item State Tree](Images/state-tree_item)
