DROP TABLE IF EXISTS definition_TB;
DROP TABLE IF EXISTS word_TB;

CREATE TABLE word_TB (
	word_ID INT PRIMARY KEY IDENTITY (1, 1),
	word VARCHAR(100) NOT NULL
);

CREATE TABLE definition_TB (
	definition_ID INTEGER PRIMARY KEY IDENTITY (1, 1),
	word_ID INT NOT NULL,
	definitions VARCHAR(1000) NOT NULL,

	CONSTRAINT word_fk_in_definitions FOREIGN KEY (word_ID)
	REFERENCES word_TB(word_ID)
);