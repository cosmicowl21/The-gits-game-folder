CREATE TABLE [dbo].[Enemy]
(
	[EnemyId] INT NOT NULL PRIMARY KEY, 
    [EnemyType] NCHAR(10) NULL, 
    [PlayerId] NCHAR(10) NULL 
)
