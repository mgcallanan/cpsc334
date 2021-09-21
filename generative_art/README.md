# Module 1, Task 2: Generative Art, "Processing Progress"

## Description

The 6 panels in Leeds Studio are an excellent opportunity to present phases of objects over time. With the visualization, the 6 panels start out dark, except for two bouncing balls on the far left. One is blue and one is pink, and the background of the panel is a combination of the two colors. They both bounce for a certain amount of time, and they progress at seemingly random times, which changes the background colors of the panels. By the end of the generative art piece, all six screens are blinking different colors as dozens of circles pound against the edges of the panels, until the installation goes black and starts over. What the viewer might not expect at first is that the progress the circles are making from panel to panel is not random, but emblematic of a wider issue that exists in the computer science industry: the uneven progression between male and female engineers.

[Click here to view a video demo of the installation in Leeds Studio.](https://youtu.be/l2ZFxiM0dEo)

## Installation: How to Run in Leeds Studio

1. Download the zip file of this repo, extract on your local computer, and navigate to the `generative-art` directory.
2. Open `generative_art.pde` in the Processing IDE on the computer.
3. Click `Ctrl` + `R` or the play button in the top left corner of the IDE
   - If you don't like the alignment of the code, then you can generate a new physical space to pixel mapping.
   - Navigate out of the `generative_art` directory and into `projector_setup`
   - Follow the instructions found in that directory's README to generate the `screen_coords.json` file
   - Delete `generative_art/screen_coords.json` and replace it with `projector_setup/screen_coords.json`
   - Repeat Step 3 until satisfied with visualization
4. The visualization should begin on its own, aligned with the screens according to `screen_coords.json`

## Usage

The visualization will run on its own after a user opens the Processing file and runs it. It resets automatically after a set number of circles have been added to the visualization due to computing resources on the Leeds Studio system. If more circles were allowed to exist, the computer would slow down until the circles appear not to move at all.

## Reproducibility

In theory, this Processing module is relatively adaptable to other spaces.

### Screen Alignment

It currently can only exist in a space similar to Leeds, in which the viewer perceives the screen as rotated 90 degrees (in other words, x-coordinates are y-coordinates and vice versa). If another artist wanted to change this, they would have to switch out the modifications made for the x-coordinates and y-coordinates in the systems (the location, velocity, and gravity) to represent the opposite occurence (for example, if a velocity vector moves in the y direction, it should move in the x direction).

### Number of Panels

The installation currently can be represented across a various number of screen panels. Due to the current meaning of the art, in terms of phases of a computer scientist's life (of which this installation presents 6), the circles will only move forward until it reaches the 6th screen. However, additional boundary parameters can be added for boundaries that exist between different panels if more than 6 are added.
