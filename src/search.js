$(function () {
	$("form").on("submit",function (e) {
		e.preventDefault() ;
		let classname = $("input[name=classname]").val() ;
		let classid = $("input[name=classid]").val() ;
		let teacher = $("input[name=teacher]").val() ;
		let groupid = $("input[name=groupid]").val() ;
	})
})

function search() {
	// body...
}