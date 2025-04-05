#  Unnamed RPG

This is *(currently)* nameless text-based 2D RPG*(-ish)* is a work-in-progress game that I felt like making. It started in **`C`**, but I decided to remake it with **`C++`** because it felt a bit easier *(I was **kind of** right about that)*.
<br>

In it, you control a little circle *(also (currently) nameless)* with `WASD` for **move**ment, `e` for **interact**ing *(though, that has yet to be implemented)*, `q` to **quit** *(the preferable way to exit)*, and `i` to see your **inventory** *(also yet to be implemented)*.
<br>

Because it is still a WIP, there are many things in store for the future of this game like... story!... more content!... actual game!... and more stuff!... Yeah, it still has some ***(a lot)*** ways to go, but I've got hope for it.
<br>

<!-- # Why?

I was learning C around the time. I was bored. Being a fan of 2D low-graphic RPGs like [UNDERTALE](https://undertale.com/), I though, "What if I made (tried to make) one of those?" I wanted to make something simple, but then my brain said, "What if we made it complicated?" So came into existence  the first prototype. Then, I started learning C++ and I though it was easier *(as long as I didn't go **too** deep)* so here we are with the remaster.
<br>
-->
# What does it look like?
In case you want to know what it looks like, there's a gif of me doing stuff in its current state in [`./extras`](extras/). If you're to lazy *(I completely understand... like... **really**)*, here's a copy and paste of the first frame.

```
ＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨ
Ｈ＃　＃　＃　＃　　　Ｈ　　　　　　　　Ｈ　ＯＨ
Ｈ　　　　　　　　　　｜　　　　　　　　｜　　Ｈ
Ｈ　　　　　　　　　　Ｈ　　　　　　　　Ｈ　　Ｈ
Ｈ　　　　　　ＨＨＨＨＨＨ　　　　　　　ＨＨＨＨＨ
Ｈ＃　　　　Ｈ　　＝＝＝　Ｈ　　　　　　　　　　Ｈ
ＨＨＨ　　ＨＨ　　　　　 　　　　　　＃　ＨＨ　[Ｈ
Ｈ　　　　　Ｈ］ 　　　　 　　　　　＃　ＨＨ　[Ｈ
Ｈ　　　　　Ｈ　　　　　　 　　　　　＃　ＨＨ　[Ｈ
Ｈ　　　　　Ｈ　　　　　　　　　　　　　　　　　Ｈ
ＨＨＨ－ＨＨＨＨＨＨＨＨＨＨ　　　　　　ＨＨＨＨＨ
　　　　　　　　　　　　　　ＨＨＨＨＨＨ　　　　　
* "Use WASD to move, Q to quit."
> 
```

`Ｈ` are walls,  
`＃` are chairs,  
`＝`, at least in this context, represent a countertop,  
`］` is a fridge (in this context)  
`［` is a TV screen,  

and that handsome `Ｏ` is you, the player (if you play the game).
Unfortunately, you wouldn't get much of that from just looking at it. Interacting will give more information, but that isn't here yet. That is one of the many challenges that come with text-based rendering on a tiny canvas (it's like pixel art... but harder somehow...).

*(Yes, it uses unicode characters which might impact compatibility, but I've have no better alternatives (at the moment).)*
<br>

# Running it

Now, to actually **play it**, you have to compile it yourself because it is not to the point where I should be focusing on building for release when half of the features aren't even in it anymore.
To **compile**, look at the [*compile the "game"*](#compile-the-game) section in [***Getting Started?***](#getting-started).
<br>

# What's to come?

There is a more detailed version of this at the bottom, but here is an overview of potential future feature:  
- Unique interactions for specific tiles  
- (Save/Settings) data files
- More maps  
- Ability to load multiple maps and enter them sequentially  
- NPCs with dialogue, options, ... and maybe more...?
- Custom tilesets made by players for players who don't agree with my choice of characters *(which I understand)*
- More languages?!
- A more customizable and powerful `.cmap` format that allows for the source file to be essentially and engine and the `.cmaps` to be easy to configure game content making it easier for UGC.
- Maybe animations?
<br>

# Contributing

But in this state, you *can* **contribute** to it.  
You can...  
- Add maps by making your own `.cmap` file [*(comprehensible example at bottom)*](#cmap-structure).  
- Add to the code to speed up development *(if you know what you are doing)*. If you know how to do something in an objectively better way, refactor! Just, don't break everything... I do that myself enough as it is.  
- You can fix bugs that I haven't gotten to yet. If you don't know how, but found a bug (which you probably will), feel free to open an issue.  
- Or maybe you have a suggestion? That's helpful too—as long as the suggestion is helpful, that is.  
- And organize code.  
  
The code is a *bit* *(just a really really really small tiny ity-bitty— It's a lot... sorry...)* disorganized, but that is soon to change once it reaches somewhere around 500 lines. Then I'll split it up and organize it better *(or at least try)*.
<br>

# Other versions

There is also the older version in [`./extras`](extras/). You can try it *(still have to compile yourself)* if you want, but I wouldn't. While it is more complete, it has a whitespace bug that makes it so you have to zoom out so tiles align, which isn't very convenient. Plus, the code is split into more files, but is still a mess.
<br>

# Getting Started?

You can...
<br>

## Clone the repository

```
git clone https://github.com/Enigma-25/RPG.git
cd  RPG
```
<br>

## Compile the "game"

To **compile**, there is no makefile yet so use your C/C++ compiler of choice or whatever is available to you, have them in the same folder and compile. Then just run the output file and you can play it *(unless it crashes; in that case... oh well...)*.
<br>

### Example with G++ (assuming your inside the `RPG` directory):

```
cd ./src
g++ main.cpp -o RPG
```
<br>

## And run the "game"

```
./RPG
```
<br>

So yeah...

<br><br><br><br><br>

...

<br><br>

...

<br><br><br><br>

......


<br><br><br><br><br><br>

................

<br><br><br><br><br><br><br><br><br>

# IM SORRY

<span title="It's a GIF kitty...">![cat gif](https://media1.tenor.com/m/w87pQ9lyF8UAAAAd/cute-aww.gif)</span>
<br>

Please accept this gif of a cat I found on the internet as my apology for this lackluster README.
<br><br><br>

## Wait..?

*Actually*, there is some stuff that could be put here *(probably shouldn't be at the bottom, but hey, ... I don't know!)* :
<br>

### To do  
- Implement interactions  
- Implement items  
- Add door functionality  
- Other stuff that I don't remember
- Remembr the stuff I didn't rememberer  
- Remmbrer to remmmeber the stuff that I didn't remeenmembr  
- Rmemmmbereber that writing rmeembbemebreber over and over again is not good for me  
  
### Ideas *(long term to do)*  
- 3D array for map coordinates (x, y) and interactions (z)  
- `prompt()` function that prompts user, typically with a question, but accepts more variable inputs  
- `config.ini` file for settings  
- `save.dat` file for save files  
- Interchangeable tilesets files  
- New `.cmap` format (in-progress)  
&nbsp;&nbsp; Multiple language support embedded into cmaps  
&nbsp;&nbsp; &nbsp;&nbsp; Planned Supported Languages  
&nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp;- English  
&nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp;- Spanish  
&nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp;- ...
  
### Cmap structure
```
[MAP]
// Provides integers to be mapped to characters for drawing of the map
// The 'a' after a number specifies the player's starting position and the number before it is the tile that is "under" the player

111111111111111111111111 12020202000a1000000001001 100000000003000000003001 100000000001000000001001 1000000111111000000011111 1200001005550100000000001 1110011000000000002011061 1000001700000000002011061 1000001000000000002011061 1000001000000000000000001 1114111111111100000011111 0000000000000011111100000


[SPECIAL]
// Declares which tiles are deemed "special" (meaning they have unique behavior when interacted with)
// The [x,y:id] specifies an id (interaction identifier) for linking of behavior with specified coordinates

1,1:1
1,5:2
3,1:3
5,1:4
7,1:5
7,7:6
9,5:7
10,5:7
11,5:7
23,6:8
23,7:9
23,8:9

/* is the same as:
1,1;1,5;3,1;5,1;7,1;7,7;9,5;10,5:6;11,5:6;23,6;23,7:7;23,8;
*/

[LANG]
ENGLISH
SPANISH
GERMAN
[EOF]

// Because this is after the [EOF] block, none of this is read by the game making it like a extras or notes section. Becuase of this, I'm going to use it to explain how lang files will work here (because I don't know what else to do)

Here is an example english.lang (with comments!):
\```
// Dialogue is linked with an ID
// Dialogue can also invoke actions through the use of `|action(arguments)|`

1:This is Chair 1. It hates Chair 4.
2:This is Chair 4. Exiled and despised for its crimes.
3:This is Chair 2. It's Chair 1's best friend. It also -- hates Chair 4.
4:This is Chair 3. It wants to be friends with Chair -- 1 and 2.
5:I don't even know who this is.
6:The fridge is empty. Maybe you'll buy groceries... -- later.
7:The counter is all nasty. What even is that substance? -- You really are irresponsible.
8:You tap on the screen. Nothing happens. What did you -- expect?
9:There's a key underneath. You pick it up. -- [You found the KEY]|ADD_ITEM(KEY)|

// Multiple dialogues with the same ID will be linked together and shown in order
:The fridge is empty. Maybe you'll buy groceries... -- later.
6:Checking again isn't going to change the fact that -- it's empty. // This has ID 6 like the previous dialogue
6:Again? This is kind of sad.

:The counter is all nasty. What even is that substance? -- You really are irresponsible. // Because three tiles have an ID of 7 and this has an ID of 7, all three tiles will have this text
:You tap on the screen. Nothing happens. What did you -- expect? // Similar logic applies here
:There's a key underneath. You pick it up. -- [You found the KEY]|ADD_ITEM(KEY)|
\```
```  
<br>
  
That's kind of all I have. This is still very early in development.