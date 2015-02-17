<?php

    // configuration
    require("../includes/config.php"); 
    require("libphp-phpmailer/class.phpmailer.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol to sell.");
        }

        else
        {
            // Find out how much of a stock they are selling
            $shares = query("SELECT shares FROM stocks WHERE id = ? AND symbol = ?",         
                $_SESSION["id"],
                $_POST["symbol"]);
            $share = $shares[0];
            $share = $share["shares"];
            
            // removing entry from DB of stock to sell          
            $query = "DELETE FROM stocks WHERE id = ".
                $_SESSION["id"]." AND symbol = '".
                $_POST["symbol"]."'";
            query($query);
          
            //find out price of sold stock
            $stock_price = lookup($_POST["symbol"]);
            $stock_price = $stock_price["price"];
            
            //give users cash for sale
            $sold_val = $share * $stock_price;
            $query = ("UPDATE users SET cash = cash + ".$sold_val." WHERE id = ". $_SESSION["id"]);
            query($query);
            refresh_user();
            
            //add to history
            history("SELL", strtoupper($_POST["symbol"]), $share, $stock_price);
            
            sendmail("SELL", strtoupper($_POST["symbol"]), $share, $stock_price);
            
            redirect('/');
        }
    }
    else
    {
        // find out what's in the portfolio
        $symbols = query("SELECT symbol FROM stocks
            WHERE id = ?", $_SESSION["id"]);
        //dump($symbols);
    
        // else render form, passing which stocks are able to be sold
        render("sell_form.php", ["title" => "Selling Stock", 
                "symbols" => $symbols]);
    }

?>
