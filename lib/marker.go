package main

import (
	"fmt"
)

func mark(
	CoreProtocolVersion int,
	protoVersion int,
	network string,
	address string,
	prototype string,
	serverCert string,
) {
	fmt.Printf("%d|%d|%s|%s|%s|%s\n",
		CoreProtocolVersion,
		protoVersion,
		network,
		address,
		prototype,
		serverCert,
	)
}
