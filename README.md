# RPG
This (currently) nameless 2D RPG(-ish) is a work-in-progress game that I felt like making. It started in C, but I decided to remake it with C++ because it felt a bit easier (I was *kind of* right about that).

In it, you control a little circle (also (currently) nameless) with WASD for movement, e for interacting (though, that has yet to be implemented), q to quit (the preferable way to exit), and i to see your inventory (also yet to be implemented).
Because it is still a WIP, there is many things in store for the future of this game like... story!... more content!... and more stuff! Yeah, it still has some (a lot) ways to go, but I've got hope for it.  
  
  
...  
  
  
  
...  
  
  
  
  
  
  
  
  
......  
  
  
  
  
  
  
  
  
  
................  
  
  
  
  
  
  
  
  
  
  
![cat gif](https://media1.tenor.com/m/w87pQ9lyF8UAAAAd/cute-aww.gif)  
Please accept this gif of a cat I found on the internet as my apology for this lackluster (and very WIP) README.  
  
  
  
  
  
  
  
  
  
  
  
Actually, there is some stuff that could be put here (probably shouldn't be at the bottom, but hey,... I don't know!):  
  
To do ::  
  - Implement interactions  
  - Implement items  
  - Add door functionality  
  - Other stuff that I can't remember  
  - Remember the stuff I didn't remember  
  - Remember to remember the stuff that I didn't remember  
  - Remember that writing rememeber over and over again is not good for me  
  
Ideas ::  
  - 3D array for map coordinates (x, y) and interactions (z)  
  - prompt() function that prompts user, typically with a question, but accepts more variable inputs  
  - config.ini file for settings  
  - save.dat file for save files  
  - Interchangeable tilesets files  
  - New .cmap format ::  
    :: Multiple language support embedded into cmaps ::  
      :: Planned Supported Languages ::  
        - English  
        - Spanish  
        - German  
  
    :: Theoretical Structure (map.cmap) (with comments! (not going to be in actual file)) ::  
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
  
That's kind of all I have. This is still very early in development.