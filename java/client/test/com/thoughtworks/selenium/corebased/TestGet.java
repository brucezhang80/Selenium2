package com.thoughtworks.selenium.corebased;

import java.util.regex.Pattern;

import com.thoughtworks.selenium.InternalSelenseTestBase;

import org.junit.Test;

// TODO(simon): The verifications should not be commented out
public class TestGet extends InternalSelenseTestBase {
	@Test public void testGet() throws Exception {
		//  test API getters 
		selenium.open("../tests/html/test_get.html");
		//  IE uppercases the property names of the style. Both Opera and Firefox
		//          lowercase the property names of the style. Both IE and Opera omit the
		//          trailing semi-colon. 
		verifyTrue(Pattern.compile("(width|WIDTH): 644px; (height|HEIGHT): 41px(;?)").matcher(selenium.getAttribute("//img[@alt='banner']@style")).find());
		//  This asserts on the current behavior of selArrayToString(). Commas and
		//          backslashes are escaped in array values. Backslash-craziness!! 
		verifyTrue(join(selenium.getSelectOptions("selectWithFunkyValues"), ',').matches("^foo[\\s\\S]*$"));
//		verifyTrue(join(selenium.getSelectOptions("selectWithFunkyValues"), ',').matches("^javascript\\{ \\[ 'foo', '\\\\,\\\\\\\\\\\\\\\\bar\\\\\\\\\\\\\\\\\\\\,', '[\\s\\S]*baz[\\s\\S]*' \\]\\.join\\(','\\) \\}$"));
//		verifyEquals(join(selenium.getSelectOptions("selectWithFunkyValues"), ','), selenium.getEval(" 'regexp:' + [ 'foo', '\\\\\\,\\\\\\\\\\\\\\\\bar\\\\\\\\\\\\\\\\\\\\\\,', '\\\\u00a0{2}baz\\\\u00a0{2}' ].join(',') "));
	}
}
