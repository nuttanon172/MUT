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
		var Emps = []Emp{}
		for rows.Next() {
			var emp Emp
			err := rows.Scan(&emp.SSN, &emp.FNAME, &emp.LNAME)
			if err != nil {
				panic(err)
			}
			Emps = append(Emps, emp)
		}
		c.JSON(200, Emps)
	})
	/*r.GET("/users/:id", func(c *gin.Context) {
	      id := c.Param("id")
	      for _, user := range users {
	          if id == user.ID {
	              c.JSON(200, user)
	              return
	          }
	      }
	      c.JSON(404, gin.H{"message": "User not found"})
	  })
	  r.POST("/users", func(c *gin.Context) {
	      var newUser User
	      if err := c.ShouldBindJSON(&newUser); err != nil {
	          c.JSON(400, gin.H{"error": err.Error()})
	          return
	      }
	      newUser.ID = len(users) + 1
	      users = append(users, newUser)
	      c.JSON(201, newUser)
	  })
	  r.PUT("/users/:id", func(c *gin.Context) {
	      id := c.Param("id")
	      for i, user := range users {
	          if id == user.ID {
	              if err := c.ShouldBindJSON(&user); err != nil {
	                  c.JSON(400, gin.H{"error": err.Error()})
	                  return
	              }
	              users[i] = user
	              c.JSON(200, user)
	              return
	          }
	      }
	      c.JSON(404, gin.H{"message": "User not found"})
	  })
	  r.DELETE("/users/:id", func(c *gin.Context) {
	      id := c.Param("id")
	      for i, user := range users {
	          if id == user.ID {
	              users = append(users[:i], users[i+1:]...)
	              c.JSON(200, gin.H{"message": "User deleted"})
	              return
	          }
	      }
	      c.JSON(404, gin.H{"message": "User not found"})
	  })*/
	r.Run(":8080")
}
