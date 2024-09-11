package main

import (
	"database/sql"
	"fmt"
	"github.com/gin-gonic/gin"
	_ "github.com/sijms/go-ora/v2"
)

type Emp struct {
	SSN   string `json:"ssn"`
	FNAME string `json:"fname"`
	LNAME string `json:"lname"`
}

var Emps = []Emp{}

func main() {
	r := gin.Default()
	r.Static("/static", "./static")
	r.GET("/users", func(c *gin.Context) {
		if len(Emps) == 0 {
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
			rows, err := db.Query("SELECT SSN,FNAME,LNAME FROM EMPLOYEE")
			if err != nil {
				panic(err)
			}
			defer rows.Close()
			for rows.Next() {
				var emp Emp
				err := rows.Scan(&emp.SSN, &emp.FNAME, &emp.LNAME)
				if err != nil {
					panic(err)
				}
				Emps = append(Emps, emp)
			}
		} else {
			c.JSON(200, Emps)
		}
	})
	r.GET("/users/:ssn", func(c *gin.Context) {
		id := c.Param("ssn")
		for _, emp := range Emps {
			if id == emp.SSN {
				c.JSON(200, emp)
				return
			}
		}
		c.JSON(404, gin.H{"message": "User not found"})
	})
	r.POST("/users", func(c *gin.Context) {
		var newUser Emp
		if err := c.ShouldBindJSON(&newUser); err != nil {
			c.JSON(400, gin.H{"error": err.Error()})
			return
		}
		for _, emp := range Emps {
			if newUser.SSN == emp.SSN {
				c.JSON(409, gin.H{"message": "Conflict Data already Exists"})
				return
			}
		}
		Emps = append(Emps, newUser)
		c.JSON(201, newUser)
	})
	r.PUT("/users/:ssn", func(c *gin.Context) {
		ssn := c.Param("ssn")
		for i, emp := range Emps {
			if ssn == emp.SSN {
				if err := c.ShouldBindJSON(&emp); err != nil {
					c.JSON(400, gin.H{"error": err.Error()})
					return
				}
				Emps[i] = emp
				c.JSON(200, emp)
				return
			}
		}
		c.JSON(404, gin.H{"message": "User not found"})
	})
	r.DELETE("/users/:ssn", func(c *gin.Context) {
		ssn := c.Param("ssn")
		for i, emp := range Emps {
			if ssn == emp.SSN {
				Emps = append(Emps[:i], Emps[i+1:]...)
				c.JSON(200, gin.H{"message": "User deleted"})
				return
			}
		}
		c.JSON(404, gin.H{"message": "User not found"})
	})
	r.Run(":8080")
}
