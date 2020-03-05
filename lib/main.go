package main

//pseudo import

import "C"

import (
	"fmt"
	"math"
	"sort"
	"sync"
)

var count int
var mtx sync.Mutex

//export Add
func Add(a, b int) int {
	return a + b
}

//export Cosine
func Cosine(x float64) float64 {
	return math.Cos(x)
}

//export Sort
func Sort(vals []int) {
	sort.Ints(vals)
}

//export Log
func Log(msg string) int {
	mtx.Lock()
	defer mtx.Unlock()
	fmt.Println(msg)
	count++
	return count
}

//export Cert
func Cert() *C.char {
	return createEncodedCert()
}

//export Mark
func Mark(
	CoreProtocolVersion int,
	protoVersion int,
	network *C.char,
	address *C.char,
	prototype *C.char,
	serverCert *C.char,
) {
  mark(CoreProtocolVersion, protoVersion, C.GoString(network), C.GoString(address), C.GoString(prototype), C.GoString(serverCert))
}

func main() {}
