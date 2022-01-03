/*
Rotary Encoder - Polling Example

The circuit:
* encoder pin A to Arduino pin 2
* encoder pin B to Arduino pin 3
* encoder ground pin to ground (GND)
*/

#include <MD_REncoder.h>



#define INCREMENTER 0.01f
#define BUTTON_PIN 13
#define BAUD_RATE 9600


// set up encoder objects
MD_REncoder P1 = MD_REncoder(5, 4);
MD_REncoder P2 = MD_REncoder(7, 6);
MD_REncoder P3 = MD_REncoder(9, 8);
MD_REncoder P4 = MD_REncoder(11, 10);


// message types
enum Messages : uint8_t
{
    SendAll = 0,        // Send all
    Brightness = 1,     // change brighness
    FFTScale = 2,       // update FFTScale
    DBScale = 3,        // update DB Scale
    SilentModeMsg = 10,
    MusicModeMsg = 11,      // change to music mode
    AmbientModeMsg = 12,    // change to ambient
    Red = 6,            // change r component of ambient
    Green = 7,          // change g component of ambient
    Blue = 8,           // change b component of ambient
    FreqPerBin = 9      // for placing bins
};



// state
enum States : uint8_t
{
    SilentMode,
    MusicMode,
    AmbientMode
};


static States state = States::SilentMode;
static Messages state_msg = Messages::SilentModeMsg;


template <typename T>
void send_message(Messages msg, T value)
{
    Serial.print(msg);
    Serial.print(" ");
    Serial.println(value);
}


void change_state()
{
  if (state == States::SilentMode)
  {
    state = States::AmbientMode;
    state_msg = Messages::AmbientModeMsg;
  }
    
  else if (state == States::AmbientMode)
  {
    state = States::MusicMode;
    state_msg = Messages::MusicModeMsg;
  }
    
  else if (state == States::MusicMode)
  {
    state = States::SilentMode;
    state_msg = Messages::SilentModeMsg;
  }
    
}


/*
POTI
*/

// starting values
float POTI1 = 0.5;
float POTI2 = 0.5;
float POTI3 = 0.5;
float POTI4 = 0.5;

void check_bounds(float& f)
{
  if (f < 0.0f)
    f = 0.0f;
  else if (f > 1.0f)
    f = 1.0f;
}

void process_poti(MD_REncoder& poti, float& poti_val, Messages msg)
{
  
  uint8_t x = poti.read();
  if (x)
  {
    poti_val += x == DIR_CW ? -INCREMENTER : INCREMENTER;
    check_bounds(poti_val);
    send_message<float>(msg, poti_val);    
  }
}

/*
BUTTON
*/
int buttonStatus = 1;
bool buttonPressed = 0;

void process_button()
    {
    int pinValue = digitalRead(BUTTON_PIN);
    if (buttonStatus != pinValue)
    {    
        // is pressed?
        if (pinValue == 0)
            // was pressed?
            if (!buttonPressed)
            {
                buttonPressed = 1;
                // change state
                change_state();
                send_message<float>(state_msg, 1.0f);
            }
            
            
        }
        else
            buttonPressed = 0;
}




void setup() 
{

  Serial.begin(BAUD_RATE);

  // button
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // potis
  P1.begin();
  P2.begin();
  P3.begin();
  P4.begin();
}

void message_handle()
{}

void loop() 
{
  // check for input
  message_handle();

  // process button press
  process_button();

  // process poti state
  if (!state == States::SilentMode)
  {
    if (state == States::MusicMode)
    {
        process_poti(P1, POTI1, Messages::Brightness);
        process_poti(P2, POTI2, Messages::FFTScale);
        process_poti(P3, POTI3, Messages::DBScale);
        process_poti(P4, POTI4, Messages::FreqPerBin);
    }
    else if (state == States::AmbientMode)
    {
        process_poti(P1, POTI1, Messages::Brightness);
        process_poti(P2, POTI2, Messages::Red);
        process_poti(P3, POTI3, Messages::Green);
        process_poti(P4, POTI4, Messages::Blue);
    }
  }
  
  
}