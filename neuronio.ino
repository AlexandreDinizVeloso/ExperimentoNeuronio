#include <EulerSolver.hpp>
#include <IzhikevichModel.hpp>

//ode::IzhikevichModel myneuron(0.02f, 0.2f, -65.0f, 8.0f); // RS
ode::IzhikevichModel myneuron(0.02f, 0.2f, -50.0f, 2.0f); //CH
ode::EulerSolver<ode::IzhikevichModel> mysolver1;
float currentTime = 0.0f;
int timeMeasurementPin = 8;

void setup() {
  Serial.begin(9600);
  analogWriteResolution(12);
  pinMode(timeMeasurementPin, OUTPUT);
}

void loop() {
  digitalWrite(timeMeasurementPin, HIGH);
  mysolver1.Step(myneuron, 10.0f, 0.8f);
  
  float currentState[2] = {myneuron.getState()[0], myneuron.getState()[1]};
  if (currentState[0] >= 30.0f) {
    currentState[0] = myneuron.getParams('c');
    currentState[1] += myneuron.getParams('d');
    myneuron.setState(currentState);
  }

  currentTime += 0.1f;
  //Serial.println(currentState[0]);
  int neuronOutput = (int)(currentState[0] * 100);
  int dacOutput = map(neuronOutput, -7500, 3000, 0, 2048);
  analogWrite(DAC0, dacOutput);
  digitalWrite(timeMeasurementPin, LOW);
}
