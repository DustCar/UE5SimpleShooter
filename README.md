# About Project
A project I completed from the UDemy course: "Unreal Engine 5 C++ Developer: Learn C++ & Make Video Games" by Ben Tristem and GameDev.tv team, Section 6, with slight additions.

I completed the main course on August 6th with this project being the final section of the course.

![UE5_Cpp_LearnCpp_MakeVideoGames_Cert](https://github.com/user-attachments/assets/c14fa1f7-4439-4bfb-b6c3-fae4672133a6)

In this course, I had to create multiple projects with increasing complexity after each project completion. Each project had its own topics it focused on (which I list out under [Course Takeaways](#Project-Takeaways)) and somewhat built upon the previous. This project was the last project of the course and is a simple third-person shooter game that includes AI enemies, simple movement with jumping, simple movement and aiming animations, simple gun FX, a HUD, controller support, and a simple elimination gamemode.

**After I completed the course, I added a few slight additions as part of a challenge set by the instructor and as part of what I wanted to add to the last project in the course, which is this project. Those additions including:**
- Setting up a gun class for ease of creating different weapons
- Adding a projectile-based weapon
- Creating a pickup class
- Creating ammo pickups and replenishing all weapon ammo
- Weapon swap functionality with scroll wheel and num keys

*_Last Updated: Aug. 10, 2024_

**If you want to skip to the showcase, [click here](#Project-Showcase), if not then I will be explaining a bit more about what I learned in this project and about why some things are how are they are in the project.**

I ultimately decided to move on to another course that focuses on Multiplayer and developing with networking in mind since I believe that networking is important to learn. So this project will be more simple that what I am currently working on. After all, this project was part of a beginners course into Unreal Engine.

In addition, since this project only had a portion of the course focused on it, some things were not added that could have made the game look smoother and feel smoother, like character rotating animations and reload animations, and I have not yet gone about adding them (at least as of last date posted above).

I used this course as a structured learning experience to get into Unreal Engine as I made the switch to it from Unity after December 2023. It took me some time to complete this project while going on and off (approx. 5 months of active learning) but it did pretty good in exposing me to what Unreal has to offer as well how C++ works with Blueprints. 

## Project Takeaways
Simple Shooter had a set of topics that it focuses more on rather than being general. However, it does build upon the previous sections and so I will also cover what I learned from earlier sections in addition to what Simple Shooter taught me.

*_The list that I will be creating below will only be a general takeaway and I may miss some specifics. Additionally, since this course covers beginners in both UE5 and C++, I may ommit some topics about C++ as I am more focused on UE5 additions and have some experience with C++ and programming already._

### Course Takeaways
This includes the main topics I learned from the earlier sections of the course.

<ins>General Blueprint and Unreal Logic (Section 2):</ins>
- Blueprint Event Graph and nodes introduction
- Asset importing
- Data types, variables, and functions

<ins>C++ introduction in UE5 (Section 3):</ins>
- Unreal Engine function and variable introductions:
  - BeingPlay(), Tick(), DeltaTime, FRotator, FString, etc.
  - UE_LOG for debugging
- Blueprint Child Classes from C++ classes

<ins>Level Design with Additional C++ (Section 4):</ins>
- Modular level design and layout using Medieval Dungeon assets
- Lighting and Lumen
- Line tracing/sweep introduction, Out parameters, TArrays, Actor tags, etc...

<ins>Pawn creation and HUD introduction in C++ (Section 5):</ins>
- Component construction using CreateDefaultSubobject<>()
- using UPROPERTY() for exposing variables to Blueprints
- Enhanced Input Subsystem
- Introduction to Widget blueprint (HUD)
- Introduction to FX (Particle System, SoundBase, and Camera Shake

### Simple Shooter Takeaways
In this section I go over the major points that Simple Shooter focuses on. It revisits many of the topics from previous sections while having a larger focus on animations and AI enemies.

Revisits:
- Enhanced Input Subsystem
- FXs (Particles, Sound)
- Line Tracing for hit scan
- HUD

New Takeaways:
- Skeletons and skeletal animations, Animation state machines, aim offsets
- Blendspaces and animations
- Spawning actors at runtime
- Creating a new actor class for guns
- Virtual methods for TakeDamage and in general
- Behavior Trees and Blackboards in C++ and BPs, BT Decorators and Selectors
- BTTasks and custom BTTasks, BTServices and custom BTServices
- many more...

For a course that is meant for beginners, it packs a lot of good introductory info that I can't all mention here but those were just some of the major things that I learned from it. I definitely need more practice but it did good in introducing Unreal Engine to me.

## Project Showcase
Here will be a set of videos showcasing certain aspects of the project and a brief description of how I went about it.

### Character

### Weapons

### AI

### HUD


