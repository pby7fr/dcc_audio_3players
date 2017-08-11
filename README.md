# dcc_audio_3players

This an Arduino software for controlling 3 DFPlayer Mini MP3 Player For Arduino with for ambiance sounds with DCC.
Support different sounds for day and night. Could be connected to a fast clock via a JMRI script.

DCC CV:

DCC address: CV003

Factory reset: CV008 
  Set to 008 for reset.

Mute volume:  CV135
  Default: 1

Sound Player 1 volume:  CV141
  From 0 to 30, default 15
  
Sound Player 2 volume:  CV142
  From 0 to 30, default 15  
  
Sound Player 3 volume:  CV143
  From 0 to 30, default 15  

Auto transition: CV145
  If bigger than 0, will change automatically day/night mode after the value (in minute)

Transition duraration:  CV146
  Length in second of the transition sound files

All players use transition:  CV150

Sound Player 1 uses transition:  CV151

Sound Player 2 uses transition:  CV152

Sound Player 3 uses transition:  CV153
