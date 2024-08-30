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
	fmt.Fprintf(w, "</form></body></html>")

}

func RecvData(w http.ResponseWriter, r *http.Request) {
	col, err := strconv.Atoi(r.FormValue("col"))
	if err != nil {
		fmt.Fprintf(w, "<h1>Error Col Atoi</h1>")
	}
	row, err := strconv.Atoi(r.FormValue("row"))
	if err != nil {
		fmt.Fprintf(w, "<h1>Error Row Atoi</h1>")
	}
	for j := 0; j < row; j++ {
		if j == 0 {
			fmt.Fprintf(w, "<table border=\"1\" style=\"width:40%%;\"><tbody><tr>\n")
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
	fmt.Fprintf(w, "</tbody></table\n")
}

func main() {
	http.HandleFunc("/", WelcomePage)
	http.HandleFunc("/recvdata", RecvData)
	http.ListenAndServe(":9999", nil)
}
