package main

import (
    "fmt"
)
// Go nao usa mais ( something := another )  Agora ta ( something = another )  mesmo.

var Bollean bool
var Mymsg string
var myInt, another int
var F = "Hello";

var sexteen int16

const isso_nao_muda = 33.45;

func main() {
    Mymsg := F + " World!"
    fmt.Println("\x1b[32mCONTATENEIII >>>> " + Mymsg + "\x1b[0m")

    var exArray [3]uint8  // Ja coloca tudo zerado.  Como se fosse um  ( unsigned int exArray[3] = {0}; )
    var another = []uint32{1,2,3,4,5}
    _ = another // Assim evita aquela mensagem de nao ser usado  e nao rodar ou nem compilar

    exArray[1] = 42

    fmt.Println(exArray[1])  // Last one
    fmt.Println(exArray[2])  // Last one

    var sentence = []string{"THIS", "IS", "MY", "SENTENCE"};
    fmt.Println("\n" + sentence[0] + "\n")  // THIS

    var right_half = sentence[2:]
    var left_half = sentence[0:len(right_half)]

    for x := 0; x < 2; x++ {
        fmt.Print(left_half[x] + " ")
        fmt.Println(right_half[x])
    }

//  ------------------  ADVANCED STUFFS ----------------------------------->
    myMap := map[string]int {
        "dog": 1,
        "cat": 0,
        "cactus": 2,
    }

    myMap["cactus"] += 3
    fmt.Print("CACTUS =====>  ")
    fmt.Println(myMap["cactus"])
    fmt.Print("\n\n\x1b[31m")

    delete(myMap, "dog")
//  Structs ------------------------------------------------------------------->

    type Pet struct {
        age uint8
        name string
        alive bool
        weight float64
    }

    myPets := map[string]Pet {
        "Quark": Pet {
            age: 12,
            name: "ART_SWORD",
            alive: true,
            weight: 34.32,
        },

        "cat": Pet {
            age: 19,
            name: "Dante",
            alive: true,
            weight: 17.88,
        },
    }
    fmt.Println("--------------------------------------------------------\n\x1b[33mSTRUCTURE: AGE | NAME | ALIVE | WEIGHT \x1b[0m")
    for key, value := range myPets {
        fmt.Print("\nkeys = " + key + " | value = ")
        fmt.Println(value)
    }
    fmt.Print("--------------------------------------------------------\x1b[0m")
}
