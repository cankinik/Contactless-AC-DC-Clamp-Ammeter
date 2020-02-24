# EEE-351-Course-Project
Contactless AC/DC Clamp Ammeter

A device composed of a hall effect sensor embedded in a toroidal metal core, Arduino Uno, LCD and additional circuitry that displays characteristics of current passing through a wire without contact. The system is a clamp that can be placed around a wire and adjusts itself for both AC and DC signals with up to 1A, 150Hz with a precision of around 2.2%. Additionally, OPAMPs are used to enhance the signal and filters are introduced to obtain better samples.

The toroidal core needs to be cut into two, attached to the clamp, and then the hall effect sensor must be glued to one end of the split core. Next, the output from the sensor is fed into the circuit that is provided in the pictures section, and then passed onto the Arduino. The results will be periodically updated on the LCD screen and switching between AC and DC is automatic. Treshold voltages may need to be adjusted according to environmental settings as the device is very sensitive.
