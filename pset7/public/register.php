<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // confirm that usename, password, and confirmation aren't empty
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["email"]))
        {
            apologize("You must provide your email.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if (empty($_POST["confirmation"]))
        {
            apologize("You must confirm your password.");
        }
        // confirm password + confirmation match
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords have to match.");        
        }
        else
        {        
            // add new entry to database 
           
            $ins_result = query("INSERT INTO users (username, hash, cash, email) VALUES(?, ?, 10000.00, ?)", 
            $_POST["username"], crypt($_POST["password"]), $_POST["email"]);
            
            
            // the INSERT failed, presumably because username already existed
            if ($ins_result === false)
            {
                apologize("Username taken. Please select a different username.");         
            }
            
            // sucessfully registered
            else
            {
                // query user's info from DB
                $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

                // if we found user
                if (count($rows) == 1)
                {
                    // first (and only) row
                    $row = $rows[0];

                    // remember that user's now logged in by storing user's info in session
                    $_SESSION["id"] = $row["id"];
                    $_SESSION["username"] = $row["username"];
                    $_SESSION["cash"] = $row["cash"];
                    

                    // redirect to portfolio
                    redirect("/");
                    
                }

            }
        }
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
    
?>
