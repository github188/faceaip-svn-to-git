/**
 *基本控制
 */
$(function(){
	//标题切换
	$(".center .content .title a").click(function(){
		$(".center .content .title a").removeClass("selected");
		$(this).addClass("selected");
	});
	//主机信息修改保存
	$("input.home_revise_btn").click(function(){
		//显示隐藏
		$(".home_note_ip").hide();
		$(".home_note_port").hide();
		$("input.home_port_no").show();
		$(this).hide();
		$("input.home_save_btn").show();
		//传值
		$("input.home_ip").val($(".home_note_ip").html());
		$("input.home_port").val($(".home_note_port").html());
	});
	$("input.home_save_btn").click(function(){
		//显示隐藏
		$(".home_note_ip").show();
		$(".home_note_port").show();
		$("input.home_port_no").hide();
		$(this).hide();
		$("input.home_revise_btn").show();
		//传值
		$(".home_note_ip").html($("input.home_ip").val());
		$(".home_note_port").html($("input.home_port").val());
	});
	//支持内外网控制人数//3-27
	$("input.net_revise_btn").click(function(){
		//显示隐藏
		$(".net_number_inner").hide();
		$(".net_number_outer").hide();
		$("input.net_number_input").show();
		$(this).hide();
		$("input.net_save_btn").show();
		//传值
		$("input.net_inner").val($(".net_number_inner").html());
		$("input.net_outer").val($(".net_number_outer").html());
	});
	$("input.net_save_btn").click(function(){
		//显示隐藏
		$(".net_number_inner").show();
		$(".net_number_outer").show();
		$("input.net_number_input").hide();
		$(this).hide();
		$("input.net_revise_btn").show();
		//传值
		$(".net_number_inner").html($("input.net_inner").val());
		$(".net_number_outer").html($("input.net_outer").val());
	});
	//配置索取
	$("input.receive_btn").click(function(){
		$('body').append('<div class="popupbg"></div><div class="popupbox"><div class="popupbox_bg"><div class="popupbox_btn_ok"><div class="popupbox_btn_cancel"><div class="popupboxbackground"><table width="100%" border="0" cellpadding="0" cellspacing="0"><tr height="28"><td></td></tr><tr height="75"><td>配置索取后需要重启，是否确定?</td></tr><tr height="40"><td><input type="button" class="popup_receive_ok" value="确定"/><input type="button" class="popup_receive_cancel" value="取消"/></td></tr></table></div></div></div></div></div>');
		$("input.popup_receive_ok").click(function(){//确认
			//删除对话框
			$(".popupbg").remove();
			$(".popupbox").remove();
			control_host('info=1&',0);
		});
		$("input.popup_receive_cancel").click(function(){//取消
			//删除对话框
			$(".popupbg").remove();
			$(".popupbox").remove();
		});
	});
	//软件更新
	$("input.renew_btn").click(function(){
		$('body').append('<div class="popupbg"></div><div class="popupbox"><div class="popupbox_bg"><div class="popupbox_btn_ok"><div class="popupbox_btn_cancel"><div class="popupboxbackground"><table width="100%" border="0" cellpadding="0" cellspacing="0"><tr height="28"><td></td></tr><tr height="75"><td>软件更新后需要重启，是否确定?</td></tr><tr height="40"><td><input type="button" class="popup_renew_ok" value="确定"/><input type="button" class="popup_renew_cancel" value="取消"/></td></tr></table></div></div></div></div></div>');
		$("input.popup_renew_ok").click(function(){//确认
			//删除对话框
			$(".popupbg").remove();
			$(".popupbox").remove();
			control_host('info=2&',0);
		});
		$("input.popup_renew_cancel").click(function(){//取消
			//删除对话框
			$(".popupbg").remove();
			$(".popupbox").remove();
		});
	});
	//主机导入选择文件
	$("input.select_file_btn").click(function(){
		//alert($("input:file").val());
		//alert($("input[name='file_upload']").val());		
	});	
});