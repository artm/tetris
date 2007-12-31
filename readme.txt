slak tetris - a tetris by Artem Baguinski <femistofel@gmail.com>

I have wrote this game during five evenings of my vacation, as an
hommage to the DOS and MSX tetrissen - the programs that introduced
computer graphics to me in the 80s. Developed on OSX and later ported
to Linux and Windows.

.h files are commented thoroughly, .cpp files - where the point isn't
obvious. I try to keep functions short and simple and properly named
though. In tetris I didn't have to sacrifice legibility for efficiency
because there just isn't much happenning.

the code files are split in two groups:

slak/glui - generic SDL+OpenGL based GUI utilities

  app.h, app.cpp - application class.  
  - initialize the libraries and run the game. application object also
    encapsulates event handling which is based on SDL events.
    Application may handle events itself (e.g. quit request) or pass
    it to current screen (see below).

  screen.h, screen.cpp - game screen class.
    - game screen is defined by its event handler and rendering
      function. screen may contain drawmodes (encapsulating OpenGL
      states) and overlays (objects drawn on top of the screen - gui
      elements, sprites, ...)

  drawmode.h - base draw mode - abstract
  overlay.h - base overlay - abstract

  Draw modes defined in the library
  ---------------------------------
  orthomode.h, orthomode.cpp - sets up OpenGL orhtoghraphic projection

  Overlays defined in the library
  -------------------------------
  rgbpic.h,rgbpic.cpp - static image overlay
  label.h,label.cpp - text overlay
  toggle.h - container overlay which shows or hides its child overlay
             depending on toggle state.
  
  Screens defined in the library
  ------------------------------
  hiscore_screen.h,hiscore_screen.cpp 
  - high score screen (including the name editor). uses
    highscore_table class.

  Utilities
  ---------
  gl-include.h - platform independent OpenGL inclusion
  pulse.h, pulse.cpp - boolean pulse signal generator - returns true
  or false dependent on current time (used for blinking effect in tetris).

slak/tetris - the game itself

  GAME LOGIC
  ----------
  tetris.h,tetris.cpp - game logic
  - this object handles actual process of playing the game and
    provides interface for controlling the falling block. 

  tetrad.h,tetrad.cpp - the tetris block mask
  - a mask on a grid, individual blocks as well as the game field are
    represented as such mask. This object implements primitive
    operations on game masks such as creation, rotation, collision
    testing, overlaying (falling block on a field), merging (once the
    block is finally fallen), finding and removing complete
    lines. could be explained as "teris math" module.
 
    the name is a misnomer, it reflects the history of the code
    (previously field wasn't derived from a tetrad). It is 

  field.h,field.cpp - tetris playing field
  - a combination of a large mask (the field) and a small one (the
    falling block) and an API for moving the little block around the    
    empty areas of the large. 

  GLUI BASED APPLICATION
  ----------------------
  tetris_app.h,tetris_app.cpp - tetris game application class

  root_menu.h,root_menu.cpp - game menu screen
  tetris_screen.h,tetris_screen.cpp - man tetris screen

  renderer.h,renderer.cpp - glui overlay that renders a game field

  MISC
  ----
  soundm.h,soundm.cpp - SDL_mixer based sound manager
  main.cpp - initialization. creates the tetris::app and calls it's
  run().

