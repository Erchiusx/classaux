var block , day , schedule;
var timetable, timetableMountingPoint;

fetch( "./block.efml" )
	.then( x => x.text() )
	.then( x => block = ef.create(x) )
	.then( fetchDay )

function fetchDay(){
	var tempDay;
	fetch( "./day.efml" )
		.then( x => x.text() )
		.then( x => { 
			tempDay = ef.create(x); 
			day = class extends tempDay {
				constructor( efArgs , indicator /* indicating if this is the first line */ ){
					super( efArgs );
					if( indicator ){
						this.blocks.push( new block({
							$data: {
								indicator: "早八"
							}
						}) )
						this.blocks.push( new block({
							$data: {
								indicator: "上午"
							}
						}) )
						this.blocks.push( new block({
							$data: {
								indicator: "下午1"
							}
						}) )
						this.blocks.push( new block({
							$data: {
								indicator: "下午2"
							}
						}) )
						this.blocks.push( new block({
							$data: {
								indicator: "晚课"
							}
						}) )
					}
					else
						for( let i = 5 ; i-- ; )
							this.blocks.push( new block() )
				}
				display( dailyPlan ){
					for( let i in dailyPlan ){
						this.blocks[i].$data.classname = dailyPlan[i]?.classname??"" ;
						this.blocks[i].$data.classID = dailyPlan[i]?.classID??"";
						this.blocks[i].$data.Teacher = dailyPlan[i]?.Teacher??"";
					}
				}
			}
		} )
		.then( fetchSchedule )
}

function fetchSchedule(){
	var tempSchedule;
	fetch( "./schedule.efml" )
		.then( x => x.text() )
		.then( x => { 
			tempSchedule = ef.create(x) ;
			schedule = class extends tempSchedule{
				constructor( efArgs , plan ){
					super( efArgs );
					this.days.push( new day( undefined , true ) )
					for( let i = 7 ; i-- ; )
						this.days.push( new day() );
				}
				display( plan ){
					for( let i of this.days )
						i.display( Array.from( { length: 5 } , () => {} ) );
					if( plan instanceof Array )
						for( let i in plan )
							this.days[i-0+1].display( plan[i] );
				}
			}
		} )
		.then( () => {
			timetable = new schedule;
			timetableMountingPoint = document.getElementById('timetable');
			timetable.$mount( { target: timetableMountingPoint , option: "replace" } );
			schedule.refresh = () =>{ timetable = new schedule ; timetable.display() ; timetable.$mount( { target: document.querySelector( "div.schedule" ) , option: "replace"})};
		} )
}