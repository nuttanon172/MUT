package main

import (
	"database/sql"
	"fmt"
	_ "github.com/sijms/go-ora/v2"
)

func main() {
	dsn := "oracle://db671006:56834@203.188.54.7:1521/database"
	db, err := sql.Open("oracle", dsn)
	if err != nil {
		panic(err)
	}
	defer db.Close()
	err = db.Ping()
	if err != nil {
		panic(err)
	}
	fmt.Println("Connected to Oracle Database using go-ora!")

	rows, err := db.Query("SELECT SSN, FNAME, LNAME FROM EMPLOYEE")
	if err != nil {
		panic(err)
	}
	defer rows.Close()
	for rows.Next() {
		var employeeID int
		var firstName, lastName string
		err := rows.Scan(&employeeID, &firstName, &lastName)
		if err != nil {
			panic(err)
		}
		fmt.Printf("Employee ID: %d, Name: %s %s\n", employeeID, firstName, lastName)
	}
}
