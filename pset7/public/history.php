<?php

    // configuration
    require("../includes/config.php"); 

    // look up rows from table
    $rows = query("SELECT timestamp, buysell, symbol, price, shares FROM history 
        WHERE userid = ? ORDER BY timestamp desc", $_SESSION["id"]);
    //dump($rows);   
    
    // store rows as positions
    $transactions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $transactions[] = [
                "timestamp" => $row["timestamp"],
                "buysell" => $row["buysell"],
                "symbol" => $row["symbol"],
                "name" => $stock["name"],
                "price" => $row["price"],
                "shares" => $row["shares"],
            ];
        }
    }
    //refresh user
    refresh_user();
    
    // render portfolio
    render("history.php", ["title" => "Transaction History", 
        "transactions" => $transactions, 
        $_SESSION["cash"] => "cash" ]);

?>
