# Voi Scooter Hack

Recently we've got one of the Voi Scooter Voiager 1.
Usually you have to unlock them with your smartphone and the right app, so we tried to bypass this.  
**We were successful.**

We did a lot of investigation, but this is only the final writeup.

![IMG_20190810_124650](https://user-images.githubusercontent.com/53583708/62821286-015cc180-bb73-11e9-92af-c33dca10b4fa.jpg)

First we removed the black controll box, unscrewed it and removed the interior. We kept the black cable with the green plug. 

![IMG_20190810_125655](https://user-images.githubusercontent.com/53583708/62821347-bf804b00-bb73-11e9-9658-e9b63131ea33.jpg)

The cable colors are: 

```
RED    -> +34VDC  
BLACK  -> GND  
BLUE   -> ENABLE  
YELLOW -> TX (3.3V !!)  
GREEN  -> RX  
```

We added a buck converter to reduce the Voltage from 34V to 3.3V. 
This is powering an Arduino Pro Mini and a HC-06 bluetooth module. 

```
GREEN  -> Arduino D10  
YELLOW -> Arduino D11  
BLUE   -> Arduino D12  
```

The bluetooth module is connected as follows: 

```
BT TX -> Arduino D8  
BT RX -> Arduino D9  
```

On Pin D3 we attached the already existing Buzzer. 

![IMG_20190810_130433](https://user-images.githubusercontent.com/53583708/62821441-26523400-bb75-11e9-964a-fd15916d9900.jpg)

![IMG_20190810_130425](https://user-images.githubusercontent.com/53583708/62821484-f22b4300-bb75-11e9-830d-130dfea5b490.jpg)

We've added an IMU for shaking recognition as anti theft, but it is not implemented yet. 

The rest of the magic is happening in the code.  
Ask if you've got questions.   

## Future improvements

- IMU implementation
- Powersafing mode for bluetooth
- Use ENABLE pin for deactivation on charging
- Replace bluetooth with NFC

