<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a stock symbol to look up.");
        }

        else
        {
            $stock = lookup($_POST["symbol"]);
            
            if (empty($stock))
            {
                apologize("Invalid stock symbol.");
            }
            else
            {
                render("../templates/quote.php", ["title" => "Quote", "stock" => $stock]);
            }
           
        }
    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
