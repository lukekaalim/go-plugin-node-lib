package main

import "encoding/base64"
import "crypto/tls"
import "C"

func createEncodedCert() *C.char {
	certPEM, keyPEM, err := generateCert()
	if err != nil {
		panic(err)
	}

	cert, err := tls.X509KeyPair(certPEM, keyPEM)
	if err != nil {
		panic(err)
	}

	serverCert := base64.RawStdEncoding.EncodeToString(cert.Certificate[0])

	return C.CString(serverCert)
}
