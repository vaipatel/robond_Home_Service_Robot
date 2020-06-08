# Home Service Robot

## Gotchas

### Initial heading incorrect

I had to set an initial pose angle to get the kobuki pointing in the correct direction before testing the navigating-to-goal behavior. I did this by setting the `initial_pose_a` launch param via the command line, using the `initial_pose_a:=WHATEVER_ANGLE` syntax, wherever I was launching the `amcl.launch` file from a shell script. In my case WHATEVER_ANGLE turned out to be -1.57 rads (-pi/2 rads).
