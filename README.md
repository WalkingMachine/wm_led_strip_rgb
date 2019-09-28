# wm_led_strip_rgb

### Launch

    roscore 
    rosrun rosserial-python serial-node.py <port-name>

### Topic 

    rostopic pub /Led_Stripe/RGB <Color msg>

### Message

When publishing on /Led_Stripe/RGB you may write a value from 0 to 255 on each color. 
Which will set the intensity of that color for the Led_Stripe.

You may also send a value to the 'A' parameter of the RGBA msg to send a blink command.

The blink mode will then put a a period equal to twice the 'A' parameter value.
