#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

int main() {
  //rate di campionamento (numero di campioni per secondo)
  const unsigned SAMPLE_RATE = 44100;
  //ampiezza: non superare i 32000 in totale (16000 x onda) onde evitare distorsioni
  //volendo si potrebbero sovrapporre anche onde di ampiezza diversa
  const unsigned AMPLITUDE = 16000;
  const double TWO_PI = 6.28318;
  double f1, f2;
  std::cout << "*********** BATTIMENTI ***********" << std::endl;
  std::cout << "Inserisci la frequenza della prima onda sonora: ";
  std::cin >> f1;

  std::cout << "Inserisci la frequenza della seconda onda sonora: ";
  std::cin >> f2;

  const double increment1 = f1/SAMPLES;
  const double increment2 = f2/SAMPLES;
  
  //trovo frequenza di battimento
  double f_beat = std::abs(f1-f2);
  double T_beat = 1/f_beat;
  //riproduco il suono per un'intervallo di tempo pari
  //al periodo di battimento
  double samples = T_beat * 44100;
  const unsigned SAMPLES = (unsigned int)samples;
  double x1 = 0, x2 = 0;
  
  //genero un array di tipo Int16 (richiesto dalla libreria)
  //che contiene i valori di ampiezza dell'onda sonora ad intervalli di tempo regolari
  //dati dal rate impostato sopra
  sf::Int16 raw[SAMPLES];
  for (unsigned i = 0; i < SAMPLES; i++) {
    raw[i] = AMPLITUDE * ( sin(x1*TWO_PI) + sin(x2*TWO_PI) );
    x1 += increment1;
    x2 += increment2;
  }

  //carico il buffer:vedasi documentazione libreria SFML
  sf::SoundBuffer Buffer;
  //verifico corretto caricamento
  if (!Buffer.loadFromSamples(raw, SAMPLES, 1, SAMPLE_RATE)) {
    std::cerr << "Loading failed!" << std::endl;
    return 1;
  }

  //avvio riproduzione del suono in loop
  sf::Sound Sound;
  Sound.setBuffer(Buffer);
  Sound.setLoop(true);
  Sound.play();
  while (1) {
    //imposto sleep di 100 ms per non sovraccaricare il sistema
    sf::sleep(sf::milliseconds(100));
  }
  return 0;
}
