<?php

    // configuration
    require("../includes/config.php"); 

    // look up rows from table
    $rows = query("SELECT symbol, shares FROM stocks WHERE id = ?", 
        $_SESSION["id"]);
       
    // store rows as positions
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    //refresh user
    refresh_user();
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", 
        "positions" => $positions, 
        $_SESSION["cash"] => "cash" ]);

?>
