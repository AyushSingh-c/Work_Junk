let mysql = require('mysql')

class Database {

	constructor() {
		this.connection = mysql.createConnection({
			host: '127.0.0.1',
			user: 'purchaseUser',
			password: 'rh0x01',
			database: 'purchasedb'
		});
	}

	async connect() {
		return new Promise((resolve, reject)=> {
			this.connection.connect((err)=> {
				if(err)
					reject(err);
				resolve();
			});
		})
	}

    async getUser(user) {
		return new Promise(async (resolve, reject) => {
			let stmt = `SELECT * FROM users WHERE username = ?`;
			this.connection.query(
                stmt,
                [
                    String(user)
                ],
                (err, result) => {
                    if(err)
                        reject(err);

                    try {
                        resolve(JSON.parse(JSON.stringify(result)))
                    }
                    catch (e) {
                        reject(e)
                    }
			})
		});
	}

    async registerUser(user, pass) {
		return new Promise(async (resolve, reject) => {
			let stmt = `INSERT INTO users (username, password) VALUES ( ?, ?)`;

            this.connection.query(
                stmt,
                [
                    String(user),
                    String(pass)
                ],
                (err, result) => {
                    if(err)
                        reject(err);

                    resolve()
			})
		});
	}

	async loginUser(user, pass) {
		return new Promise(async (resolve, reject) => {
			let stmt = `SELECT username FROM users WHERE username = ? and password = ?`;

            this.connection.query(
                stmt,
                [
                    String(user),
                    String(pass)
                ],
                (err, result) => {
                    if(err)
                        reject(err);

                    try {
                        resolve(JSON.parse(JSON.stringify(result)));
                    }
                    catch (e) {
                        reject(e);
                    }
			})
		});
	}

    async listProducts(approved=1) {
		return new Promise(async (resolve, reject) => {
			let stmt = `SELECT * FROM requestlist WHERE approved = ?`;

			this.connection.query(
                stmt,
                [
                    parseInt(approved)
                ],
                (err, result) => {
                    if(err)
                        reject(err);

                    try {
                        resolve(JSON.parse(JSON.stringify(result)));
                    }
                    catch (e) {
                        reject(e);
                    }
			})
		});
	}

}

module.exports = Database;