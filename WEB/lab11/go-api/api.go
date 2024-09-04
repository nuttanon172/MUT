package main

import (
	"github.com/gin-gonic/gin"
	"strconv"
)

type User struct {
	ID    int    `json:"id"`
	Name  string `json:"name"`
	Email string `json:"email"`
}

var users = []User{
	{ID: 1, Name: "Alice", Email: "alice@example.com"},
	{ID: 2, Name: "Bob", Email: "bob@example.com"},
}

func main() {
	r := gin.Default()
	r.GET("/users", func(c *gin.Context) {
		c.JSON(200, users)
	})
	r.GET("/users/:id", func(c *gin.Context) {
		id := c.Param("id")
		for _, user := range users {
			if id == strconv.Itoa(user.ID) {
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
			if id == strconv.Itoa(user.ID) {
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
			if id == strconv.Itoa(user.ID) {
				users = append(users[:i], users[i+1:]...)
				c.JSON(200, gin.H{"message": "User deleted"})
				return
			}
		}
		c.JSON(404, gin.H{"message": "User not found"})
	})
	r.Run(":8080")
}
