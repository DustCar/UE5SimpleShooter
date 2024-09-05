# About Project
A project I completed from the UDemy course: "Unreal Engine 5 C++ Developer: Learn C++ & Make Video Games" by Ben Tristem and GameDev.tv team, Section 6, with slight additions.

I completed the main course on August 6th with this project being the final section of the course.

![UE5_Cpp_LearnCpp_MakeVideoGames_Cert](https://github.com/user-attachments/assets/c14fa1f7-4439-4bfb-b6c3-fae4672133a6)

In this course, I had to create multiple projects with increasing complexity after each project completion. Each project had its own topics it focused on (which I list out under [Project Takeaways](#Project-Takeaways)) and somewhat built upon the previous. This project was the last project of the course and is a simple third-person shooter game that includes AI enemies, simple movement with jumping, simple movement and aiming animations, simple gun FX, a HUD, controller support, and a simple elimination gamemode.

**After I completed the course, I added a few slight additions as part of a challenge set by the instructor and as part of what I wanted to add to the last project in the course, which is this project. Those additions including:**
- Setting up a gun class for ease of creating different weapons
- Adding a projectile-based weapon
- Creating a pickup class
- Creating ammo pickups and replenishing all weapon ammo
- Weapon swap functionality with scroll wheel and num keys

*_Last Updated: Aug. 10, 2024_

I have ultimately decided to move on to another course that focuses on Multiplayer and developing with networking in mind since I believe that networking is important to learn. So this project will be more simple that what I am currently working on. After all, this project was part of a beginners course into Unreal Engine.

**If you want to skip to the showcase, [click here](#Project-Showcase), if not then I will be explaining a bit more about what I learned in this project and about why some things are how are they are in the project.**

Since this project only had a portion of the course focused on it, some things were not added that could have made the game look smoother and feel smoother, like character rotating animations and reload animations, and I have not yet gone about adding them (at least as of last date posted above).

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
https://github.com/user-attachments/assets/fe9ee841-06ab-4245-8e9e-a0fc432d9c78

For character movement I used the Enhance Input Subsystem and formatted it in a way to keep the Character header file cleaner by avoiding to declare Input Actions in it. I did this by saving Input Actions into a Custom Data Asset file and referencing it when binding actions in Character.cpp

**Custom Data Asset:**

Member declaraction in header file to reference in Character.cpp (no need for a .ccp file for the DA)

![SSCDAH](https://github.com/user-attachments/assets/5ac71dcc-fa1f-4277-b001-bd54078d0ec1)

Blueprint version where I assign the Input Actions to their respective member variables

![SSCDA](https://github.com/user-attachments/assets/e42c83bb-99b2-4cc5-9888-949e75e7955b)

I then reference the Data Asset along with my own IMC with all the mapping for the IAs

![SSCH](https://github.com/user-attachments/assets/110da3c4-c0a7-4420-a98a-ad6e021fe345)

Then in the Character.cpp file, I would manually set up the Enhanced Input Component by obtaining the Player Controller using `GetController()` with casting, obtaining the Enhanced Input Local Player Subsystem using the Player Controller, clearing all IMCs and adding our own, then binding the IAs to our call back functions, referencing the Data Asset with our IAs to pass in to the function.

![SSBIA](https://github.com/user-attachments/assets/2a9e183c-da7f-4d29-bd9e-bd2138740aee)

After setup in Character.cpp, I go to the Character BP and assign the Data Asset and IMC to the character so that it can properly setup the EIS.

![SSCBPEI](https://github.com/user-attachments/assets/f6cc89b2-dce1-408c-9684-aeb50d65fce7)

Now if I want to add any future Input Actions, I would just declare the member in the Data Asset, rather than character.h, and then bind the action in the character.cpp file after creating the Input Action and assigning a mapping to it in the IMC.

### Weapons
https://github.com/user-attachments/assets/fc377fc7-1d1e-4415-a4df-3f0a65d84ff3

For weapons, I created a base Actor class named Gun, which held variables that were common between any gun like a Skeletal Mesh, SFX (Sound, Particles), Ammo, Firing function, and some extra functions and variables. For some functions, like the firing function, they were made to be virtual methods to be able to override the function based on what kind of gun it is.

I then created two child classes of the Gun class, _HitScan_ and _Projectile_. Keeping it broad so that it can be used to create multiple weapons based on type rather than creating a class for each weapon. For both classes I overrode the firing function, `PullTrigger()`, so that _HitScan_ would use a trace as the main way to deal damage, while _Projectile_ also uses a trace but spawns a projectile instead for the damage, only using the trace for projectile rotation.

**HitScan PullTrigger():**

![SSHGPT](https://github.com/user-attachments/assets/304a791c-c42f-4cb2-a0b3-a2b1edb3291b)

**Projectile PullTrigger():**

![SSPGPT](https://github.com/user-attachments/assets/8a44b94d-43c9-4aa2-8ade-80e0513e081b)

I then created Blueprints from the C++ class and this is where I named the gun to be an actual gun (i.e. _Rifle_ and _Launcher_) and then set all variables needed to give the gun life, like the Skeletal Mesh and SFX. 

To deal damage to a character, I overrode the `TakeDamage()` function in the character class so that it affects the character's Health component. For Hitscan, it used the results from the trace to directly call `TakeDamage()` for the _DamagedActor_. For the Projectile weapon, it used a projectile actor that used the function `ApplyRadialDamageWithFalloff()` in a hit event callback function I called `OnHit()` which is binded to `OnComponentHit`.

#### Weapon Reloading
For reloading, the Gun class actually holds variables and functions handling a guns ammo including variables for _AmmoInMag_ (current and max) and _ReserveAmmo_ (current and max) and functions for refreshing mags. To reload a weapon from the character, I created a callback function which would call the `RefreshMag()` function of the currently equipped gun, and binded that to a Reload IA.

The way I implemented refresh mags is by creating two local int32 variables which would hold calculated new amounts for ammo in mag and reserve ammo, _NewAmmoInMag_ and _NewReserve_ respectively. Then I would use ternary functions for the _CurrentAmmoInMag_ and _CurrentReserveAmmo_ to set them as either max amount or the calculated amount. 

**Gun Header:**

![SSGAH](https://github.com/user-attachments/assets/1b9eac33-664e-41e4-90b3-b6d177f3c75e)

**RefreshMag():**

![SSGRM](https://github.com/user-attachments/assets/f2319623-6de1-4bb9-8705-2d8bb9c0ddb3)

#### Weapon Switching
https://github.com/user-attachments/assets/29b918ed-c30c-44d8-9556-fc0dccb2d01f

**Multiple Weapon Setup:**

To understand how I did weapon switching, I will briefly explain how I handled multiple weapons and how I added them into the world. 

On my character class, it held a TStaticArray of type _ASimpleShooterGun_, my Gun class, with 2 elements, named _Guns_. The character class also declares _ASimpleShooterGun_ subclasses named _RifleClass_ and _LauncherClass_ to be used with `SpawnActor()`, and an int32 index variable for current weapon, which was defaulted to 0. 

After declaration, I then spawned the two gun actors and placed them into the _Guns_ array in index 0 and 1, Rifle first then Launcher. Then, I attached it to a socket on the character mesh using the `AttachToComponent()` function to add the weapon into the world. Then set the owner of the current weapon to that of the character.

![SSCBP](https://github.com/user-attachments/assets/eb096038-2e66-4577-8163-a619f98a0b8c)

For weapon switching, I added two ways of switching, scroll wheel or num keys 1 and 2. 

For scroll wheel, the code for attaching the weapon and setting the owner from BeginPlay() is reused to equip the other weapon after hiding the currently equipped weapon. 

![SSCSW](https://github.com/user-attachments/assets/2890b7e0-ef3a-4a5a-9b3a-5d8a07d8f451)

For num keys, I used the same code but included a parameter that holds the index of the weapon you want to switch to. So instead of updating index by incrementing, it is set to the parameter.

![SSCWSN](https://github.com/user-attachments/assets/63b395a7-6857-4aa6-a032-f7ae11986655)

Both functions return early if the character has just swapped, and the numbered returns early if the player is trying to swap to the current weapon.

### Ammo Pickup
https://github.com/user-attachments/assets/9302398b-fc41-468f-854f-44d9c41aecf4


### AI
https://github.com/user-attachments/assets/dfdbda71-9d90-4acc-875a-541128791c47


### HUD
For my HUDs, I used Widget Blueprints to design the HUDs then in the my PlayerController C++ class I declare the widget classes to reference them to add to viewport using `AddToViewport()`.

I have three Widget Blueprints:
- Main HUD with crosshair, health, and ammo
- Game Over screen
- Win screen

Both game over and win screens are just text blocks, while the main hud uses get functions for health and ammo so that it can be updated on the screen.

For the health bar, the functionality is set in the Blueprint and I just used branch nodes, comparing the percentage of the current health to a threshold then changing the color to the condition it goes to (< .7 = yellow, < .4 = red).

#### Game Over
https://github.com/user-attachments/assets/ebf5383e-5e9f-4140-bd79-bc71f6fbd585


#### Win
https://github.com/user-attachments/assets/673750c8-2468-433c-a3c3-9e109a5484fb


### Demo
Here is a really short demo of just going around the map and eliminating the enemies. As seen from the past videos and in this video, the game does spike during certain movements and this could be attributed to the map that I imported in from the course's asset packs, but I would not be surprised if it had to do with my code or machine.

https://github.com/user-attachments/assets/f1d39e44-a5af-4492-aca8-ae20407d4a7f

That is all from what I have currently done with this project. Thank you for making it this far and taking the time to read this, it can definitely be better and more polished and I may add more features later down the line, but I will keep it as is for now since I have more fun projects that I look forward to. 

It may not be too impressive but I wanted to at least showcase my start and be proud of the learning process I had with this course and project. I want to look back on this project in the future and see how far I have come.

As I said at the top of the README, I am currently working on a different project that is also a shooter but involves networking and multiplayer. It handles some aspects of gameplay a little differently than in Simple Shooter and will most likely be more polished than this one. 

I plan to dive into networking and multiplayer in hopes that I can gain the skills to work on online games and I decided to work on that project to do so. The name of that project is Arina and if you want to check it out, here is the [link](https://github.com/DustCar/UE5ArinaMultiplayerShooterProject) to it.

**Again, thank you very much for taking the time to look over this project! Hope you have a nice day!**




