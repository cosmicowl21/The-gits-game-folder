CREATE TABLE [dbo].[Coin]
(
	[CoinId] INT NOT NULL PRIMARY KEY, 
    [CoinType] NCHAR(10) NULL, 
    [CoinAmount] NCHAR(10) NULL, 
    [PlayerId] NCHAR(10) NULL
)
