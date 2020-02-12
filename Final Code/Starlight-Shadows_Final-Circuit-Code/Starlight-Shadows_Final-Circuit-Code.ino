// Starlight Shadows
// C7 Emily Campbell + Vanshika Swaika
// HCID521 WINTER 2020

// We referenced our code from:
//    Vilros Ultimate Starter Guide
//    https://learn.adafruit.com/

// Here we are defining the RGB LED breadboard inputs + outputs
// Constant integers; hard defined for the rest of the code

const int sensorPin = 0;
const int sensorPinPressure = 1;
const int redPin = 5;
const int greenPin = 6;
const int bluePin = 3;

// Here we are defining our 6 variables
// Light Levels high + low, pressure levels high + low
// This stores the reading of the sensors; sensors are constantly reading

int lightLevel, high = 0, low = 1023;
int pressure, highPressure = 0, lowPressure = 1023;

// We have to tell the Arduino which outputs to use otherwise the pin won't be turned on
// We use our variables from above to identify these outputs
  
void setup()
{
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600); // Used for debugging so that we can see what the breadboard is doing in real-time

}

// The loop is the body of work for the code to always run
// This acts like the draw function in p5js
// We have it read the pressure sensor pin and then store that information in the pressure level variable
// Then it reads the light sensor pin and stores that information in the light level variable
// From the exercise we did in class, we used the setColor function and added our variables for the light sensor and pressure sensor

void loop()
{

  pressure = analogRead(sensorPinPressure);

  lightLevel = analogRead(sensorPin);
  
  autoTune();  // This code comes from the code within the Vilros Ultimate Starter Guide booklet in their example on photo resistors
  
  setColor(255, 255, 0, 255 - lightLevel, pressure);  
}

// autoTune is a function we took and modified from Vilros Ultimate Starter Guide
// This is where we figure out the highest and lowest values that are mapped to values between 0 - 255
// The first if statement checks if the light level is lower than the lowest recorded light level and then sets the variable to that light level if it is
// The second if statement checks if the light level is higher than the highest recorded light level and sets the variable to that light level if it is
// The third if statement checks if the pressure level is lower than the lowest recorded pressure level and sets the variable to that pressure level if it is
// The fourth if statement checks if the pressure level is higher than the highest recorded pressure level and sets the variable to that pressure level if it is
// Map takes a variable (light level) then it puts that variable between low and high, then it creates an equivilency between 0 - 255

void autoTune()
{
  
  if (lightLevel < low)
  {
    low = lightLevel;
  }
  
  if (lightLevel > high)
  {
    high = lightLevel;
  }
  if (pressure < lowPressure)
  {
    lowPressure = pressure;
  }
  
  if (pressure > highPressure)
  {
    highPressure = pressure;
  }
  
  lightLevel = map(lightLevel, low+50, high-50, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
  
  pressure = map(pressure, lowPressure, highPressure, 0, 255);
  pressure = constrain(pressure, 0, 255);
  
}

// We input our red, green, and blue integers
// This code came from our in class exercise code
// We invert our light level reading because we want to have the light work when it is dark
// The readings from our sensors determine the outputs of our variables here which set the color of the RGB light displays
// We use Red + Green to produce a Yellow light
// If the room light is high, there is no light color; If the room light is low, there is a yellow light
// If the room light level is high, there is no light color; If the room light level is low and the pressure sensor is high, there is red light because we remove the green
// We do not use blue because there is a dim white light inbetween the color transition because the LED hits all the colors at once when shifting to blue
// Constrain makes sure that our number never goes over or under certain values (0 - 255)

void setColor(int red, int green, int blue, int lightLevel, int pressure)
{
  
  red = 255 - red + lightLevel;
  green = constrain((255 - green + lightLevel + pressure), 0, 255);
  blue = 255 - blue;// + lightLevel;

// Debugging code tests

  Serial.println(red);
  Serial.println(blue);
  Serial.println(green);
  Serial.println();

// This outputs the current variable to the pin
// "Write the value of red to the red pin"
  
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
