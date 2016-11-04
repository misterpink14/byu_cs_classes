drop table if exists user;
drop table if exists project;
drop table if exists field;
drop table if exists image;
drop table if exists record;


CREATE TABLE user 
(
	user_id INTEGER NOT NULL,
	user_name TEXT NOT NULL,
	password TEXT NOT NULL,
	first_name TEXT NOT NULL,
	last_name TEXT NOT NULL,
	email TEXT NOT NULL,
	indexed INTEGER NOT NULL,
	CONSTRAINT ck_indexed CHECK (indexed >= 0) 
)



CREATE TABLE project
(
	project_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	title TEXT NOT NULL,
	records_per_image INTEGER NOT NULL,
	first_y_coord INTEGER NOT NULL,
	record_height INTEGER NOT NULL,
	CONSTRAINT ck_records_per_image CHECK (records_per_image > 0),
	CONSTRAINT ck_first_y_coord CHECK (first_y_coZord >= 0),
	CONSTRAINT ck_record_height CHECK (record_height > 0) 
)



CREATE TABLE field
(
	field_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	title TEXT NOT NULL,
	x_coord INTEGER NOT NULL,
	width INTEGER NOT NULL,
	helphtml TEXT NOT NULL,
	knowndata TEXT NOT NULL,
	project_id INTEGER NOT NULL,
	CONSTRAINT ck_xcoord CHECK (x_coord >= 0),
	CONSTRAINT ck_width CHECK (width > 0) , 
	FOREIGN KEY (project_id) REFERENCES project(id)
)



CREATE TABLE image 
(
	image_id INTEGER NOT NULL,
	file TEXT NOT NULL,
	project_id INTEGER NOT NULL,
	user_id INTEGER,
	FOREIGN KEY (project_id) REFERENCES project(id)
)



CREATE TABLE record 
(
	value TEXT NOT NULL,
	row INTEGER NOT NULL,
	image_id INTEGER NOT NULL,
	field_id INTEGER NOT NULL
)