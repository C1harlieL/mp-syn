# mp-syn
## Perception and multimedia - Mini Project
## Exploring synesthesia of audio pitch and colour

Openframeworks app exploring audio synthesis and the phenomenon synethesia

Requires the Maximillian Openframeworks [addon](https://github.com/micknoise/Maximilian)

This app is a simple software synthesiser and note visualiser. I have mapped the musical notes from A0 to G#7 to a colour value so each of the twelve musical pitches in an octave has its own colour. This was done by mapping the pitch array index (from 0 to 11) to a Hue value. I displayed the notes as a grid, each line representing an octave. 

You default to octave 3 and can use the ',' and '.' keys to move down and up and octave. The keys "a s d f g h j k l ; ' # " are for the notes " A through to G# ". I chose this layout so as to display the octaves chromatically. I chose this layout to display the notes chromatically and to simply display the cyclic nature of the western tonal canon. 

The idea of colour associated with sound I borrowed from the perceptual phenomenon of synesthesia, where one cognitive pathway such as the auditory one, causes automatic involuntary experiences in a second sensory pathway, maybe the visual one. This creates the effect of people seeing sounds, maybe as colours. Certain musical keys may create visual effects of a certain colour for a synesthete. Colours in my app are used to represent the most common twelve notes used in the western tonal music as a synesthetic visualiser for the notes. Colour could help with recognising patterns in music and to see which part of the octave you are in. 

![Interface image ](https://github.com/C1harlieL/mp-syn/blob/master/interface.jpeg)

# Peer input

- "It could have controls for the parameters of the synth such as controls for the adsr envelope or the type of wave that is generated."
  I added in sliders to control the envelope, which adds more variety to the sound that can be produced.

- "Midi support would be a good expansion."

- "Sequencing abilities of some kind would be cool. A really interesting one would be to have some way to draw a patter across the grid and then have that be the sequence to play"
   I like this idea alot. You could really explore how we perceive pattern.
