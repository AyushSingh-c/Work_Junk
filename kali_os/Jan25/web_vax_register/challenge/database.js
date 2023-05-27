const sqlite = require('sqlite-async');

class Database {
	constructor(db_file) {
		this.db_file = db_file;
		this.db = undefined;
	}
	
	async connect() {
		this.db = await sqlite.open(this.db_file);
	}

	async migrate() {
		return this.db.exec(`
            DROP TABLE IF EXISTS userData;

            CREATE TABLE IF NOT EXISTS userData (
                id         INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                username   VARCHAR(255) NOT NULL UNIQUE,
                password   VARCHAR(255) NOT NULL,
                email   VARCHAR(255) NOT NULL,
                full_name VARCHAR(255),
                phone   VARCHAR(255),
                birth_date   VARCHAR(255),
                gender   VARCHAR(255),
                address_1   VARCHAR(255),
                address_2   VARCHAR(255),
                city   VARCHAR(255),
                state   VARCHAR(255),
                zip   VARCHAR(255),
                health_issues   VARCHAR(255),
                symptoms   VARCHAR(255),
                allergies   VARCHAR(255),
                c19_diagnosed   VARCHAR(255)
            );

            INSERT INTO userData (
                username, 
                password, 
                email, 
                full_name,
                phone, 
                birth_date, 
                gender, 
                address_1, 
                address_2, 
                city, 
                state, 
                zip, 
                health_issues, 
                symptoms, 
                allergies, 
                c19_diagnosed
            ) 
            VALUES (
                'admin', 
                '[REDACTED SECRET]', 
                'admin@vax-prereg.gov',
                'Edward Davis',
                '412-462-9184',
                '1983-11-15',
                'male',
                '3221 Chandler Hollow Road',
                'Goshen, AL',
                'Goshen',
                'Alabama',
                '36035',
                'none',
                'High fever',
                'none',
                'No'
            );

            DROP TABLE IF EXISTS adminStats;

            CREATE TABLE IF NOT EXISTS adminStats (
                id         INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                total_applications   VARCHAR(255) NOT NULL UNIQUE,
                total_diagnosed   VARCHAR(255) NOT NULL,
                flag   VARCHAR(255) NOT NULL
            );

            INSERT INTO adminStats (total_applications,total_diagnosed,flag) VALUES (53400,12500,'HTB{f4k3_fl4g_f0r_t3st1ng}');
            
        `);
	}

	async registerUser(user, pass, email) {
		return new Promise(async (resolve, reject) => {
			try {
				let stmt = await this.db.prepare('INSERT INTO userData (username, password, email) VALUES ( ?, ?, ?)');
				resolve((await stmt.run(user, pass, email)));
			} catch(e) {
				reject(e);
			}
		});
	}

	async loginUser(user, pass) {
		return new Promise(async (resolve, reject) => {
			try {
				let stmt = await this.db.prepare('SELECT email FROM userData WHERE username = ? and password = ?');
				resolve(await stmt.get(user, pass));
			} catch(e) {
				reject(e);
			}
		});
	}

	async getUser(user) {
		return new Promise(async (resolve, reject) => {
			try {
				let stmt = await this.db.prepare('SELECT username FROM userData WHERE email = ?');
				resolve(await stmt.get(user));
			} catch(e) {
				reject(e);
			}
		});
	}

	async checkUser(user, email) {
		return new Promise(async (resolve, reject) => {
			try {
				let stmt = await this.db.prepare('SELECT username, email FROM userData WHERE username = ? or email = ?');
				let row = await stmt.get(user, email);
				resolve(row !== undefined);
			} catch(e) {
				reject(e);
			}
		});
	}

	
	async getFormData(email) {
		return new Promise(async (resolve, reject) => {
			try {
				let stmt = await this.db.prepare('SELECT * FROM userData WHERE username = ?');
				resolve(await stmt.get(email));
			} catch(e) {
				reject(e);
			}
		});
	}

	async getStats() {
		return new Promise(async (resolve, reject) => {
			try {
				let stmt = await this.db.prepare('SELECT * FROM adminStats');
				resolve(await stmt.get());
			} catch(e) {
				reject(e);
			}
		});
	}

	async addRecord(userRecords, username) {
		return new Promise(async (resolve, reject) => {
			try {
				let validFields = "";
				let fieldRecords = [];
				for (const [ key, value ] of Object.entries(userRecords)) { 
					if (key.match(/^[a-z0-9_]+$/i)) {
						validFields += `, ${key} = ?`;
						fieldRecords.push(userRecords[key]);
					}
				}
				let sqlQuery = `UPDATE userData SET ${validFields.substring(1)} WHERE username = ?`;
				let stmt = await this.db.prepare(sqlQuery);
				resolve(await stmt.run(...fieldRecords,username));
			} catch(e) {
				reject(e);
			}
		});
	}

}

module.exports = Database;