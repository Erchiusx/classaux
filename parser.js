var table = [];
var fs = require( "fs" );

fetch( "http://127.0.0.1:8080/orz.h" )
	.then( x => x.text() )
	.then( x => x.split( /\n/g ).slice(6,-2) )
	.then( x => Array.from( x , u => {
		let temp = Array.from( u.match( /".*?"/g ) , t => t.slice( 1 , -1 ) ) ;
		temp.splice( 2 , 1 );
		let time = temp.pop().match( /\d\(.*?\)/g );
		let tempLast = {};
		try{
			for( let i of time )
				tempLast[i[0]] = Math.floor( ( i[2]-0+1 )/3 );
			temp.push( tempLast );
			table.push( temp );
		} catch( e ){;}
	} ) )
	.then( () => {
		let data = JSON.stringify( table, null, 4 );
		fs.writeFile( "./list.json" , data , "utf8" , ()=>{} );
	} )