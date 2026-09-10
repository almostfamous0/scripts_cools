package main

import (
	"fmt"
)

type Musica struct {
	Nome  string
	Plays int
}

func main() {
	musicas := []Musica{
		{Nome: "Daqui pra frente - Nx Zero", Plays: 24},
		{Nome: "Vermelho - Gloria Groove", Plays: 13},
		{Nome: "Maldivas - Ludimilla", Plays: 48},
	}

	var ordenadas []Musica

	for range musicas {
		maior := buscaMaior(musicas)
		ordenadas = append(ordenadas, musicas[maior])
		musicas = append(musicas[:maior], musicas[maior+1:]...)
	}

	fmt.Println("==>", ordenadas)
}

func buscaMaior(musicas []Musica) int {
	maior := 0
	for k, v := range musicas {
		if v.Plays > musicas[maior].Plays {
			maior = k
		}
	}

	return maior
}

