var plans = [], searchInputs = [];
var planIndex = 0;
var planSchedule = [];
var dayTimes = [ "早八" , "上午" , "下午1" , "下午2" , "晚课" ];
var countsearch = new class{
	#count = 0;
	get Count(){
		return this.#count++;
	}
}()
var search ;
var list;
var searchresultEFT ;
var resultList = function(){ let temp = ef.t`
>div.resultList
	+List
` ;
return new temp;
}();
var dataList = function(){
	let optionCount = 0;
	let optionEFT = ef.t`
	>option
		#value = {{ value = 0 }}
	`;
	let temp = ef.t`
	>input#dt
		@keydown = check
		#list = datalist
		#placeholder = "课程组编号"
	>dataList#datalist
		+options
	`
	return new temp( {
		$methods:{
			check: key => {
				if( key.event.code != "Enter" )
					return;
				if( !Array.from( this.options , x => x.$data.value ).includes( document.querySelector( "input#dt" ).value ) )
					this.options.push( new option( {
						$data: {
							value: optionCount++
						}
					} ) )
			}
		}
	} )
}
fetch( "./list.json" )
	.then( x => x.json() )
	.then( x => list = x )
fetch( "./search.efml" )
	.then( x => x.text() )
	.then( ef.create )
	.then( x => ( fetch( "searchresult.efml" )
			.then( x => x.text() )
			.then( ef.create )
			.then( x => searchresultEFT = class extends x{
				constructor( classID , classname , Teacher , time ){
					super( {
						$data: {
							classname, classID , Teacher
						},
						$methods: {
							show: ()=>{
								schedule.refresh();
								for( let i in this.time ){
									console.log( i , this.time[i] , timetable.days[i].blocks[this.time[i]].$data.classname , this.$data.classname );
									timetable.days[i].blocks[this.time[i]].$data = this.$data;
								}
							},
							ban: ()=>{ this.$umount() }
						}
					} );
					this.time = time;
				}
			} ) , 
		search = class extends x{
			constructor( placeholder ){
				super( {
					$data: {
						placeholder, countsearch: countsearch.Count
					},
					$methods: {
						blur: () => {},
						letBlur: key => {
							if( key.event.code != "Enter" )
								return;
							this.getElement().blur();
							let keywords = Array.from( searchInputs, x => x.getElement().value );
							let results = list.filter( x => x[1].includes(keywords[0]) && x[2].includes(keywords[1]) );
							console.log( results );
							resultList.List = [];
							for( let i of results )
								resultList.List.push( new searchresultEFT( ...i ) );
						}
					}
				} )
			}
			getElement(){
				return document.querySelector( `input#search${this.$data.countsearch}` );
			}
		} ) )
	.then( x => {
		let searchMountPoint = document.querySelector( "div#operations" );
		searchInputs.push( new search( "课程名称" ) , new search( "开课教师" ) );
		for( let i of searchInputs )
			i.$mount( { target: searchMountPoint } );
		resultList.$mount( { target: searchMountPoint } );
	} )
