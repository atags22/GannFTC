Heading

Introduction
Heading.c gives a filtered heading for NXT robots using robotC. It uses a Kalman filter to fuse gyro and compass readings into a heading.

Installation
Copy the heading.c file to the directory that contains source files. If you are not sure where this directory is you can look this op in the robotc preferences. Go to the tab Directories and look under Directory for source files

Usage
Include heading.c in your program: #include "heading.c";
This creates a global variable called heading (type float) that contains the output of the filter. It's value ranges from 0 to 359.99999. The value of heading is updated every 20 msec.

The filter can output information to the screen. Fo this add #define HEADING_DISPLAY before the include statement. The information shown are:
- unfiltered compass reading
- the heading calculated by the filter
- the variance of the filter. How good is the value generated by the filter
- the value of the disturbance flag. If the value is one the filter ignores the value of the compass sensor as this probably suffers from disturbances.

The filter can compensate for one of the sensor being mounted upside down. This is done by adding #define MOUNTING - before the include statement.


More information
More information can be found on my blog at nxttime.wordpress.com

Author
Aswin.bouwmeester ( at gmail.com)

Copyright
Feel free to modify or distribute