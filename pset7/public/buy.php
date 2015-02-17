<?php

    // configuration
    require("../includes/config.php"); 
    require("libphp-phpmailer/class.phpmailer.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // cast shares to int
        settype($_POST["shares"] , "integer");
        

        
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol to buy.");
        }
        
        else if ((is_int($_POST["shares"]) == false) || ($_POST["shares"] < 1))
        {       
            apologize("Please provide a valid amount.");
        }  
        
        
        else
        {        
            //find out price of sold stock
            $stock_price = lookup($_POST["symbol"]);
            if (empty($stock_price))
            {
                apologize("Invalid stock symbol.");
            }
            else
            {
                $stock_price = $stock_price["price"];
                $buy_val = $_POST["shares"] * $stock_price;
                
                //validate that user has enough cash
                refresh_user();
                if ($buy_val > $_SESSION["cash"])
                {   
                    apologize("Insufficient funds.");
                }      
                 
                             
                // Deduct cash    
                $query = ("UPDATE users SET cash = cash - ".$buy_val." WHERE id = ". $_SESSION["id"]);
                query($query);
                
                // Add stock
                $query = ("INSERT INTO stocks (id, symbol, shares) VALUES(".
                    $_SESSION["id"]. ",'". 
                    strtoupper($_POST["symbol"]). "',".
                    $_POST["shares"]. 
                    ") ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)");
                query($query);
                
                // Add to history
                history("BUY", strtoupper($_POST["symbol"]), $_POST["shares"], $stock_price);
                
                sendmail("BUY", strtoupper($_POST["symbol"]), $_POST["shares"], $stock_price);
                 
                redirect('/');
            }
        }
    }
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buying Stocks"]);
    }

?>
