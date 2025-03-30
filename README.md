#  Unnamed RPG

This *(currently)* nameless text-based 2D RPG*(-ish)* is a work-in-progress game that I felt like making. It started in **`C`**, but I decided to remake it with **`C++`** because it felt a bit easier *(I was **kind of** right about that)*.
<br>
In it, you control a little circle *(also (currently) nameless)* with `WASD` for **move**ment, `e` for **interact**ing *(though, that has yet to be implemented)*, `q` to **quit** *(the preferable way to exit)*, and `i` to see your **inventory** *(also yet to be implemented)*.
<br>
Because it is still a WIP, there are many things in store for the future of this game like... story!... more content!... actual game!... and more stuff!... Yeah, it still has some ***(a lot)*** ways to go, but I've got hope for it.
<br>

# Why?

I was learning C around the time. I was bored. Being a fan of 2D low-graphic RPGs like [UNDERTALE](https://undertale.com/), I though, "What if I made (tried to make) one of those?" I wanted to make something simple, but then my brain said, "What if we made it complicated?" So came into existence  the first prototype. Then, I started learning C++ and I though it was easier *(as long as I didn't go **too** deep)* so here we are with the remaster.
<br>

# What does it look like?
In case you want to know what it looks like, there's a gif of me doing stuff in its current state in `./show`. If you're to lazy *(I completely understand... like... **really**)*, here's a copy and paste of the first frame.

```
ＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨＨ
Ｈ＃　＃　＃　＃　　　Ｈ　　　　　　　　Ｈ　ＯＨ
Ｈ　　　　　　　　　　｜　　　　　　　　｜　　Ｈ
Ｈ　　　　　　　　　　Ｈ　　　　　　　　Ｈ　　Ｈ
Ｈ　　　　　　ＨＨＨＨＨＨ　　　　　　　ＨＨＨＨＨ
Ｈ＃　　　　Ｈ　　＝＝＝　Ｈ　　　　　　　　　　Ｈ
ＨＨＨ　　ＨＨ　　　　　　　　　　　＃　ＨＨ　［Ｈ
Ｈ　　　　　Ｈ］　　　　　　　　　　＃　ＨＨ　［Ｈ
Ｈ　　　　　Ｈ　　　　　　　　　　　＃　ＨＨ　［Ｈ
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
Unfortunatley, you wouldn't get much of that from just looking at it. Interacting will give more information, but that isn't here yet. That is one of the many challenges that come with text-based rendering on a tiny canvas (it's like pixel art... but harder somehow...).

*(Yes, it uses unicode characters which might impact compatibility, but I've have no better alternatives (at the moment).)*
<br>

# Running it

Now, to actually **play it**, you have to compile it yourself because it is not to the point where I should be focusing on building for release when half of the features aren't even in it anymore.
To **compile**, look at the *compile the "game"* section in ***Getting Started?***.
<br>

## Example:

```
g++ main.cpp -o RPG
./RPG
```
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
- Add maps by making your own `.cmap` file *(comprehensible example at bottom)*.  
- Add to the code to speed up development *(if you know what you are doing)*. If you know how to do something in an objectively better way, refactor! Just, don't break everything... I do that myself enough as it is.  
- You can fix bugs that I haven't gotten to yet. If you don't know how, but found a bug (which you probably will), feel free to open an issue.  
- Or maybe you have a suggestion? That's helpful too—as long as the suggestion is helpful, that is.  
- And organize code.  
  
The code is a *bit* *(just a really really really small tiny ity-bitty— It's a lot... sorry...)* disorganized, but that is soon to change once it reaches somewhere around 500 lines. Then I'll split it up and organize it better *(or at least try)*.
<br>

# Other versions

There is also the older version in `./show`. You can try it *(still have to compile yourself)* if you want, but I wouldn't. While it is more complete, it has a whitespace bug that makes it so you have to zoom out so tiles align, which isn't very convenient. Plus, the code is split into more files, but is still a mess.
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

### Example with G++:

```
g++ main.cpp -o RPG
```
<br>

## Run the "game"

```
./RPG
```
<br>

...

<br><br>

...

<br><br><br><br>

......


<br><br><br><br><br><br>

................

<br><br><br><br><br><br><br><br><br>

# IM SORRY

![cat gif](https://media1.tenor.com/m/w87pQ9lyF8UAAAAd/cute-aww.gif)
<br>

Please accept this gif of a cat I found on the internet as my apology for this lackluster (and very WIP) README.
<br><br><br>

## Wait..?

*Actually*, there is some stuff that could be put here *(probably shouldn't be at the bottom, but hey, ... I don't know!)* :
<br>

To do ::  
&nbsp;&nbsp;- Implement interactions  
&nbsp;&nbsp;- Implement items  
&nbsp;&nbsp;- Add door functionality  
&nbsp;&nbsp;- Other stuff that I don't remember
&nbsp;&nbsp;- Remembr the stuff I didn't rememberer  
&nbsp;&nbsp;- Remmbrer to remmmeber the stuff that I didn't remeenmembr  
&nbsp;&nbsp;- Rmemmmbereber that writing rmeembbemebreber over and over again is not good for me  
  
Ideas *(long term to do)* ::  
&nbsp;&nbsp;- 3D array for map coordinates (x, y) and interactions (z)  
&nbsp;&nbsp;- `prompt()` function that prompts user, typically with a question, but accepts more variable inputs  
&nbsp;&nbsp;- `config.ini` file for settings  
&nbsp;&nbsp;- `save.dat` file for save files  
&nbsp;&nbsp;- Interchangeable tilesets files  
&nbsp;&nbsp;- New `.cmap` format ::  
&nbsp;&nbsp;  &nbsp;&nbsp;:: Multiple language support embedded into cmaps ::  
&nbsp;&nbsp;  &nbsp;&nbsp;  &nbsp;&nbsp;:: Planned Supported Languages ::  
&nbsp;&nbsp;  &nbsp;&nbsp;  &nbsp;&nbsp;  &nbsp;&nbsp;- English  
&nbsp;&nbsp;  &nbsp;&nbsp;  &nbsp;&nbsp;  &nbsp;&nbsp;- Spanish  
&nbsp;&nbsp;  &nbsp;&nbsp;  &nbsp;&nbsp;  &nbsp;&nbsp;- German  
  
&nbsp;&nbsp;  &nbsp;&nbsp;:: Theoretical Structure (`map.cmap`) (with comments! (not going to be in actual file)) ::  
  ```
  [MAP]  
  11111111... 120202... ...  
  [START]  
  11,1  
  [SPECIAL]  
  // [x,y:OPTIONAL_DIALOGUE_ID] (presumes next integer for ID)  
  1,1;1,4;2,1;4,1;6,1;...6,6;  
  [ITEMS]  
  :KEY // [OPTIONAL_INDEX:ITEM_ID] (presumes next integer for index)  
  ...  
  [ENGLISH] // My best language  
  // [OPTIONAL_DIALOGUE_ID: [DIALOGUE || ACTIONS] ... ] (pressumes next integer for ID)  
  :This is Chair 1. It hates Chair 4.  
  :This is Chair 4. Exiled and despised for its crimes.  
  :This is Chair 2. It's Chair 1's best friend. It also -- hates Chair 4.  
  :This is Chair 3. It wants to be friends with Chair -- 1 and 1.  
  :I don't even know who this is.  
  ...  
  :There's a key underneath. You pick it up. -- [Found the KEY]|ADD_ITEM(1)  
  [SPANISH] // My first, but weaker, language  
  :Esta es Silla 1. Odia a Silla 4.  
  :Esta es Silla 4. Exiliada y despreciada por sus crímenes.  
  :Esta es Silla 2. Es el mejor amigo de Silla 1. También -- odia a Silla 4.  
  :Esta es Silla 3. Quiere ser amigo de Silla -- 1 y 1.  
  :No sé ni quién es.  
  ...  
  :Hay una llave debajo. La recoges. -- [Encontrastes la LLAVE]|ADD_ITEM(1)  
  [GERMAN] // My latest and weakest language  
  :Das ist Stuhl 1. Es hasst Stuhl 4.  
  :Das ist Stuhl 4. Verbannt und verachtet für seine Verbrechen.  
  :Das ist Stuhl 2. Es ist Stuhl 1 bester Freund. Es -- hasst auch Stuhl 4.  
  :Das ist Stuhl 3. Es will mit Stuhl -- 1 und 1 befreundet sein.  
  :Ich weiß nicht einmal, wer das ist.  
  ...  
  :Es gibt einen Schlüssel darunter. Du nimmst ihn auf. -- [du hast den SCHLÜSSEL gefunden]|ADD_ITEM(1)  
  [EOF]
  ```  
<br>
  
That's kind of all I have. This is still very early in development.