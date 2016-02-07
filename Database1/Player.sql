CREATE TABLE [dbo].[Player]
(
	[PlayerId] INT NOT NULL PRIMARY KEY, 
    [PlayerName] NCHAR(10) NULL, 
    [PlayerDeath] INT NULL, 
    [EnemiesKilled] INT NULL
)
