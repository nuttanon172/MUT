package main

import (
	"fmt"
	"net/http"
	"strconv"
)

var Counter int = 0

type Student struct {
	name  string
	lname string
	age   int
}

func add(a int, b int) int {
	return a + b
}

func WelcomePage(w http.ResponseWriter, r *http.Request) {
	cookie := http.Cookie{
		Name:     "nt",
		Value:    "Maha",
		Path:     "/",
		HttpOnly: true,
	}
	http.SetCookie(w, &cookie)
	Counter++
	fmt.Fprintf(w, "<html><body><form action=\"/recvdata\" method=\"post\"> Counter: "+strconv.Itoa(Counter)+" Welcome to my page<br>")
	fmt.Fprintf(w, "Colum <input type=\"text\" name=\"col\"><br>")
	fmt.Fprintf(w, "Row <input type=\"text\" name=\"row\"><br>")
	fmt.Fprintf(w, "<input type=\"submit\" name=\"Send\">")
	//fmt.Fprintf()
	fmt.Fprintf(w, "</form></body></html>")

}

func RecvData(w http.ResponseWriter, r *http.Request) {
	col, cerr := strconv.Atoi(r.FormValue("col"))
	row, rerr := strconv.Atoi(r.FormValue("row"))
	for j := 0; j < row; j++ {
		if j == 0 {
			fmt.Fprintf(w, "<table border=1><tr>\n")
		} else {
			fmt.Fprintf(w, "<tr>\n")
		}
		for i := 0; i < col; i++ {
			if j == 0 {
				fmt.Fprintf(w, "<th>1</th>\n")
			} else {
				fmt.Fprintf(w, "<td>1</td>\n")
			}
		}
		fmt.Fprintf(w, "</tr>\n")
	}
	fmt.Fprintf(w, "</table\n")
	fmt.Fprintf(w, "tm", cerr, rerr)

}

func main() {
	fs := http.FileServer(http.Dir("./static"))
	http.Handle("/", fs)
	http.HandleFunc("/ww", WelcomePage)
	http.HandleFunc("/recvdata", RecvData)
	http.ListenAndServe(":9999", nil)
}
