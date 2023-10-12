#ifndef BENCHMARK_LOG_MSG_H_
#define BENCHMARK_LOG_MSG_H_

#include <stdint.h>
#include <vector>

struct LogMsg {
	uint64_t u64;
	uint32_t u32;
	int64_t i64;
	int32_t i32;
	char s[128];
};

void GenLogMsgArray(uint32_t cnt, std::vector<LogMsg> &log_msgs);

bool DumpsLogMsg(std::vector<LogMsg> &log_msgs);

bool LoadLogMsg(std::vector<LogMsg> &log_msgs);

#define EXPAND_FUNCS                                                     \
	typedef void (*fn_log_func)(LogMsg & msg);                           \
	LOG_FUNC(0)                                                          \
	LOG_FUNC(1)                                                          \
	LOG_FUNC(2)                                                          \
	LOG_FUNC(3)                                                          \
	LOG_FUNC(4)                                                          \
	LOG_FUNC(5)                                                          \
	LOG_FUNC(6)                                                          \
	LOG_FUNC(7)                                                          \
	LOG_FUNC(8)                                                          \
	LOG_FUNC(9)                                                          \
	LOG_FUNC(10)                                                         \
	LOG_FUNC(11)                                                         \
	LOG_FUNC(12)                                                         \
	LOG_FUNC(13)                                                         \
	LOG_FUNC(14)                                                         \
	LOG_FUNC(15)                                                         \
	LOG_FUNC(16)                                                         \
	LOG_FUNC(17)                                                         \
	LOG_FUNC(18)                                                         \
	LOG_FUNC(19)                                                         \
	LOG_FUNC(20)                                                         \
	LOG_FUNC(21)                                                         \
	LOG_FUNC(22)                                                         \
	LOG_FUNC(23)                                                         \
	LOG_FUNC(24)                                                         \
	LOG_FUNC(25)                                                         \
	LOG_FUNC(26)                                                         \
	LOG_FUNC(27)                                                         \
	LOG_FUNC(28)                                                         \
	LOG_FUNC(29)                                                         \
	LOG_FUNC(30)                                                         \
	LOG_FUNC(31)                                                         \
	LOG_FUNC(32)                                                         \
	LOG_FUNC(33)                                                         \
	LOG_FUNC(34)                                                         \
	LOG_FUNC(35)                                                         \
	LOG_FUNC(36)                                                         \
	LOG_FUNC(37)                                                         \
	LOG_FUNC(38)                                                         \
	LOG_FUNC(39)                                                         \
	LOG_FUNC(40)                                                         \
	LOG_FUNC(41)                                                         \
	LOG_FUNC(42)                                                         \
	LOG_FUNC(43)                                                         \
	LOG_FUNC(44)                                                         \
	LOG_FUNC(45)                                                         \
	LOG_FUNC(46)                                                         \
	LOG_FUNC(47)                                                         \
	LOG_FUNC(48)                                                         \
	LOG_FUNC(49)                                                         \
	LOG_FUNC(50)                                                         \
	LOG_FUNC(51)                                                         \
	LOG_FUNC(52)                                                         \
	LOG_FUNC(53)                                                         \
	LOG_FUNC(54)                                                         \
	LOG_FUNC(55)                                                         \
	LOG_FUNC(56)                                                         \
	LOG_FUNC(57)                                                         \
	LOG_FUNC(58)                                                         \
	LOG_FUNC(59)                                                         \
	LOG_FUNC(60)                                                         \
	LOG_FUNC(61)                                                         \
	LOG_FUNC(62)                                                         \
	LOG_FUNC(63)                                                         \
	LOG_FUNC(64)                                                         \
	LOG_FUNC(65)                                                         \
	LOG_FUNC(66)                                                         \
	LOG_FUNC(67)                                                         \
	LOG_FUNC(68)                                                         \
	LOG_FUNC(69)                                                         \
	LOG_FUNC(70)                                                         \
	LOG_FUNC(71)                                                         \
	LOG_FUNC(72)                                                         \
	LOG_FUNC(73)                                                         \
	LOG_FUNC(74)                                                         \
	LOG_FUNC(75)                                                         \
	LOG_FUNC(76)                                                         \
	LOG_FUNC(77)                                                         \
	LOG_FUNC(78)                                                         \
	LOG_FUNC(79)                                                         \
	LOG_FUNC(80)                                                         \
	LOG_FUNC(81)                                                         \
	LOG_FUNC(82)                                                         \
	LOG_FUNC(83)                                                         \
	LOG_FUNC(84)                                                         \
	LOG_FUNC(85)                                                         \
	LOG_FUNC(86)                                                         \
	LOG_FUNC(87)                                                         \
	LOG_FUNC(88)                                                         \
	LOG_FUNC(89)                                                         \
	LOG_FUNC(90)                                                         \
	LOG_FUNC(91)                                                         \
	LOG_FUNC(92)                                                         \
	LOG_FUNC(93)                                                         \
	LOG_FUNC(94)                                                         \
	LOG_FUNC(95)                                                         \
	LOG_FUNC(96)                                                         \
	LOG_FUNC(97)                                                         \
	LOG_FUNC(98)                                                         \
	LOG_FUNC(99)                                                         \
	LOG_FUNC(100)                                                        \
	LOG_FUNC(101)                                                        \
	LOG_FUNC(102)                                                        \
	LOG_FUNC(103)                                                        \
	LOG_FUNC(104)                                                        \
	LOG_FUNC(105)                                                        \
	LOG_FUNC(106)                                                        \
	LOG_FUNC(107)                                                        \
	LOG_FUNC(108)                                                        \
	LOG_FUNC(109)                                                        \
	LOG_FUNC(110)                                                        \
	LOG_FUNC(111)                                                        \
	LOG_FUNC(112)                                                        \
	LOG_FUNC(113)                                                        \
	LOG_FUNC(114)                                                        \
	LOG_FUNC(115)                                                        \
	LOG_FUNC(116)                                                        \
	LOG_FUNC(117)                                                        \
	LOG_FUNC(118)                                                        \
	LOG_FUNC(119)                                                        \
	LOG_FUNC(120)                                                        \
	LOG_FUNC(121)                                                        \
	LOG_FUNC(122)                                                        \
	LOG_FUNC(123)                                                        \
	LOG_FUNC(124)                                                        \
	LOG_FUNC(125)                                                        \
	LOG_FUNC(126)                                                        \
	LOG_FUNC(127)                                                        \
	LOG_FUNC(128)                                                        \
	LOG_FUNC(129)                                                        \
	LOG_FUNC(130)                                                        \
	LOG_FUNC(131)                                                        \
	LOG_FUNC(132)                                                        \
	LOG_FUNC(133)                                                        \
	LOG_FUNC(134)                                                        \
	LOG_FUNC(135)                                                        \
	LOG_FUNC(136)                                                        \
	LOG_FUNC(137)                                                        \
	LOG_FUNC(138)                                                        \
	LOG_FUNC(139)                                                        \
	LOG_FUNC(140)                                                        \
	LOG_FUNC(141)                                                        \
	LOG_FUNC(142)                                                        \
	LOG_FUNC(143)                                                        \
	LOG_FUNC(144)                                                        \
	LOG_FUNC(145)                                                        \
	LOG_FUNC(146)                                                        \
	LOG_FUNC(147)                                                        \
	LOG_FUNC(148)                                                        \
	LOG_FUNC(149)                                                        \
	LOG_FUNC(150)                                                        \
	LOG_FUNC(151)                                                        \
	LOG_FUNC(152)                                                        \
	LOG_FUNC(153)                                                        \
	LOG_FUNC(154)                                                        \
	LOG_FUNC(155)                                                        \
	LOG_FUNC(156)                                                        \
	LOG_FUNC(157)                                                        \
	LOG_FUNC(158)                                                        \
	LOG_FUNC(159)                                                        \
	LOG_FUNC(160)                                                        \
	LOG_FUNC(161)                                                        \
	LOG_FUNC(162)                                                        \
	LOG_FUNC(163)                                                        \
	LOG_FUNC(164)                                                        \
	LOG_FUNC(165)                                                        \
	LOG_FUNC(166)                                                        \
	LOG_FUNC(167)                                                        \
	LOG_FUNC(168)                                                        \
	LOG_FUNC(169)                                                        \
	LOG_FUNC(170)                                                        \
	LOG_FUNC(171)                                                        \
	LOG_FUNC(172)                                                        \
	LOG_FUNC(173)                                                        \
	LOG_FUNC(174)                                                        \
	LOG_FUNC(175)                                                        \
	LOG_FUNC(176)                                                        \
	LOG_FUNC(177)                                                        \
	LOG_FUNC(178)                                                        \
	LOG_FUNC(179)                                                        \
	LOG_FUNC(180)                                                        \
	LOG_FUNC(181)                                                        \
	LOG_FUNC(182)                                                        \
	LOG_FUNC(183)                                                        \
	LOG_FUNC(184)                                                        \
	LOG_FUNC(185)                                                        \
	LOG_FUNC(186)                                                        \
	LOG_FUNC(187)                                                        \
	LOG_FUNC(188)                                                        \
	LOG_FUNC(189)                                                        \
	LOG_FUNC(190)                                                        \
	LOG_FUNC(191)                                                        \
	LOG_FUNC(192)                                                        \
	LOG_FUNC(193)                                                        \
	LOG_FUNC(194)                                                        \
	LOG_FUNC(195)                                                        \
	LOG_FUNC(196)                                                        \
	LOG_FUNC(197)                                                        \
	LOG_FUNC(198)                                                        \
	LOG_FUNC(199)                                                        \
	LOG_FUNC(200)                                                        \
	LOG_FUNC(201)                                                        \
	LOG_FUNC(202)                                                        \
	LOG_FUNC(203)                                                        \
	LOG_FUNC(204)                                                        \
	LOG_FUNC(205)                                                        \
	LOG_FUNC(206)                                                        \
	LOG_FUNC(207)                                                        \
	LOG_FUNC(208)                                                        \
	LOG_FUNC(209)                                                        \
	LOG_FUNC(210)                                                        \
	LOG_FUNC(211)                                                        \
	LOG_FUNC(212)                                                        \
	LOG_FUNC(213)                                                        \
	LOG_FUNC(214)                                                        \
	LOG_FUNC(215)                                                        \
	LOG_FUNC(216)                                                        \
	LOG_FUNC(217)                                                        \
	LOG_FUNC(218)                                                        \
	LOG_FUNC(219)                                                        \
	LOG_FUNC(220)                                                        \
	LOG_FUNC(221)                                                        \
	LOG_FUNC(222)                                                        \
	LOG_FUNC(223)                                                        \
	LOG_FUNC(224)                                                        \
	LOG_FUNC(225)                                                        \
	LOG_FUNC(226)                                                        \
	LOG_FUNC(227)                                                        \
	LOG_FUNC(228)                                                        \
	LOG_FUNC(229)                                                        \
	LOG_FUNC(230)                                                        \
	LOG_FUNC(231)                                                        \
	LOG_FUNC(232)                                                        \
	LOG_FUNC(233)                                                        \
	LOG_FUNC(234)                                                        \
	LOG_FUNC(235)                                                        \
	LOG_FUNC(236)                                                        \
	LOG_FUNC(237)                                                        \
	LOG_FUNC(238)                                                        \
	LOG_FUNC(239)                                                        \
	LOG_FUNC(240)                                                        \
	LOG_FUNC(241)                                                        \
	LOG_FUNC(242)                                                        \
	LOG_FUNC(243)                                                        \
	LOG_FUNC(244)                                                        \
	LOG_FUNC(245)                                                        \
	LOG_FUNC(246)                                                        \
	LOG_FUNC(247)                                                        \
	LOG_FUNC(248)                                                        \
	LOG_FUNC(249)                                                        \
	LOG_FUNC(250)                                                        \
	LOG_FUNC(251)                                                        \
	LOG_FUNC(252)                                                        \
	LOG_FUNC(253)                                                        \
	LOG_FUNC(254)                                                        \
	LOG_FUNC(255)                                                        \
	LOG_FUNC(256)                                                        \
	LOG_FUNC(257)                                                        \
	LOG_FUNC(258)                                                        \
	LOG_FUNC(259)                                                        \
	LOG_FUNC(260)                                                        \
	LOG_FUNC(261)                                                        \
	LOG_FUNC(262)                                                        \
	LOG_FUNC(263)                                                        \
	LOG_FUNC(264)                                                        \
	LOG_FUNC(265)                                                        \
	LOG_FUNC(266)                                                        \
	LOG_FUNC(267)                                                        \
	LOG_FUNC(268)                                                        \
	LOG_FUNC(269)                                                        \
	LOG_FUNC(270)                                                        \
	LOG_FUNC(271)                                                        \
	LOG_FUNC(272)                                                        \
	LOG_FUNC(273)                                                        \
	LOG_FUNC(274)                                                        \
	LOG_FUNC(275)                                                        \
	LOG_FUNC(276)                                                        \
	LOG_FUNC(277)                                                        \
	LOG_FUNC(278)                                                        \
	LOG_FUNC(279)                                                        \
	LOG_FUNC(280)                                                        \
	LOG_FUNC(281)                                                        \
	LOG_FUNC(282)                                                        \
	LOG_FUNC(283)                                                        \
	LOG_FUNC(284)                                                        \
	LOG_FUNC(285)                                                        \
	LOG_FUNC(286)                                                        \
	LOG_FUNC(287)                                                        \
	LOG_FUNC(288)                                                        \
	LOG_FUNC(289)                                                        \
	LOG_FUNC(290)                                                        \
	LOG_FUNC(291)                                                        \
	LOG_FUNC(292)                                                        \
	LOG_FUNC(293)                                                        \
	LOG_FUNC(294)                                                        \
	LOG_FUNC(295)                                                        \
	LOG_FUNC(296)                                                        \
	LOG_FUNC(297)                                                        \
	LOG_FUNC(298)                                                        \
	LOG_FUNC(299)                                                        \
	LOG_FUNC(300)                                                        \
	LOG_FUNC(301)                                                        \
	LOG_FUNC(302)                                                        \
	LOG_FUNC(303)                                                        \
	LOG_FUNC(304)                                                        \
	LOG_FUNC(305)                                                        \
	LOG_FUNC(306)                                                        \
	LOG_FUNC(307)                                                        \
	LOG_FUNC(308)                                                        \
	LOG_FUNC(309)                                                        \
	LOG_FUNC(310)                                                        \
	LOG_FUNC(311)                                                        \
	LOG_FUNC(312)                                                        \
	LOG_FUNC(313)                                                        \
	LOG_FUNC(314)                                                        \
	LOG_FUNC(315)                                                        \
	LOG_FUNC(316)                                                        \
	LOG_FUNC(317)                                                        \
	LOG_FUNC(318)                                                        \
	LOG_FUNC(319)                                                        \
	LOG_FUNC(320)                                                        \
	LOG_FUNC(321)                                                        \
	LOG_FUNC(322)                                                        \
	LOG_FUNC(323)                                                        \
	LOG_FUNC(324)                                                        \
	LOG_FUNC(325)                                                        \
	LOG_FUNC(326)                                                        \
	LOG_FUNC(327)                                                        \
	LOG_FUNC(328)                                                        \
	LOG_FUNC(329)                                                        \
	LOG_FUNC(330)                                                        \
	LOG_FUNC(331)                                                        \
	LOG_FUNC(332)                                                        \
	LOG_FUNC(333)                                                        \
	LOG_FUNC(334)                                                        \
	LOG_FUNC(335)                                                        \
	LOG_FUNC(336)                                                        \
	LOG_FUNC(337)                                                        \
	LOG_FUNC(338)                                                        \
	LOG_FUNC(339)                                                        \
	LOG_FUNC(340)                                                        \
	LOG_FUNC(341)                                                        \
	LOG_FUNC(342)                                                        \
	LOG_FUNC(343)                                                        \
	LOG_FUNC(344)                                                        \
	LOG_FUNC(345)                                                        \
	LOG_FUNC(346)                                                        \
	LOG_FUNC(347)                                                        \
	LOG_FUNC(348)                                                        \
	LOG_FUNC(349)                                                        \
	LOG_FUNC(350)                                                        \
	LOG_FUNC(351)                                                        \
	LOG_FUNC(352)                                                        \
	LOG_FUNC(353)                                                        \
	LOG_FUNC(354)                                                        \
	LOG_FUNC(355)                                                        \
	LOG_FUNC(356)                                                        \
	LOG_FUNC(357)                                                        \
	LOG_FUNC(358)                                                        \
	LOG_FUNC(359)                                                        \
	LOG_FUNC(360)                                                        \
	LOG_FUNC(361)                                                        \
	LOG_FUNC(362)                                                        \
	LOG_FUNC(363)                                                        \
	LOG_FUNC(364)                                                        \
	LOG_FUNC(365)                                                        \
	LOG_FUNC(366)                                                        \
	LOG_FUNC(367)                                                        \
	LOG_FUNC(368)                                                        \
	LOG_FUNC(369)                                                        \
	LOG_FUNC(370)                                                        \
	LOG_FUNC(371)                                                        \
	LOG_FUNC(372)                                                        \
	LOG_FUNC(373)                                                        \
	LOG_FUNC(374)                                                        \
	LOG_FUNC(375)                                                        \
	LOG_FUNC(376)                                                        \
	LOG_FUNC(377)                                                        \
	LOG_FUNC(378)                                                        \
	LOG_FUNC(379)                                                        \
	LOG_FUNC(380)                                                        \
	LOG_FUNC(381)                                                        \
	LOG_FUNC(382)                                                        \
	LOG_FUNC(383)                                                        \
	LOG_FUNC(384)                                                        \
	LOG_FUNC(385)                                                        \
	LOG_FUNC(386)                                                        \
	LOG_FUNC(387)                                                        \
	LOG_FUNC(388)                                                        \
	LOG_FUNC(389)                                                        \
	LOG_FUNC(390)                                                        \
	LOG_FUNC(391)                                                        \
	LOG_FUNC(392)                                                        \
	LOG_FUNC(393)                                                        \
	LOG_FUNC(394)                                                        \
	LOG_FUNC(395)                                                        \
	LOG_FUNC(396)                                                        \
	LOG_FUNC(397)                                                        \
	LOG_FUNC(398)                                                        \
	LOG_FUNC(399)                                                        \
	LOG_FUNC(400)                                                        \
	LOG_FUNC(401)                                                        \
	LOG_FUNC(402)                                                        \
	LOG_FUNC(403)                                                        \
	LOG_FUNC(404)                                                        \
	LOG_FUNC(405)                                                        \
	LOG_FUNC(406)                                                        \
	LOG_FUNC(407)                                                        \
	LOG_FUNC(408)                                                        \
	LOG_FUNC(409)                                                        \
	LOG_FUNC(410)                                                        \
	LOG_FUNC(411)                                                        \
	LOG_FUNC(412)                                                        \
	LOG_FUNC(413)                                                        \
	LOG_FUNC(414)                                                        \
	LOG_FUNC(415)                                                        \
	LOG_FUNC(416)                                                        \
	LOG_FUNC(417)                                                        \
	LOG_FUNC(418)                                                        \
	LOG_FUNC(419)                                                        \
	LOG_FUNC(420)                                                        \
	LOG_FUNC(421)                                                        \
	LOG_FUNC(422)                                                        \
	LOG_FUNC(423)                                                        \
	LOG_FUNC(424)                                                        \
	LOG_FUNC(425)                                                        \
	LOG_FUNC(426)                                                        \
	LOG_FUNC(427)                                                        \
	LOG_FUNC(428)                                                        \
	LOG_FUNC(429)                                                        \
	LOG_FUNC(430)                                                        \
	LOG_FUNC(431)                                                        \
	LOG_FUNC(432)                                                        \
	LOG_FUNC(433)                                                        \
	LOG_FUNC(434)                                                        \
	LOG_FUNC(435)                                                        \
	LOG_FUNC(436)                                                        \
	LOG_FUNC(437)                                                        \
	LOG_FUNC(438)                                                        \
	LOG_FUNC(439)                                                        \
	LOG_FUNC(440)                                                        \
	LOG_FUNC(441)                                                        \
	LOG_FUNC(442)                                                        \
	LOG_FUNC(443)                                                        \
	LOG_FUNC(444)                                                        \
	LOG_FUNC(445)                                                        \
	LOG_FUNC(446)                                                        \
	LOG_FUNC(447)                                                        \
	LOG_FUNC(448)                                                        \
	LOG_FUNC(449)                                                        \
	LOG_FUNC(450)                                                        \
	LOG_FUNC(451)                                                        \
	LOG_FUNC(452)                                                        \
	LOG_FUNC(453)                                                        \
	LOG_FUNC(454)                                                        \
	LOG_FUNC(455)                                                        \
	LOG_FUNC(456)                                                        \
	LOG_FUNC(457)                                                        \
	LOG_FUNC(458)                                                        \
	LOG_FUNC(459)                                                        \
	LOG_FUNC(460)                                                        \
	LOG_FUNC(461)                                                        \
	LOG_FUNC(462)                                                        \
	LOG_FUNC(463)                                                        \
	LOG_FUNC(464)                                                        \
	LOG_FUNC(465)                                                        \
	LOG_FUNC(466)                                                        \
	LOG_FUNC(467)                                                        \
	LOG_FUNC(468)                                                        \
	LOG_FUNC(469)                                                        \
	LOG_FUNC(470)                                                        \
	LOG_FUNC(471)                                                        \
	LOG_FUNC(472)                                                        \
	LOG_FUNC(473)                                                        \
	LOG_FUNC(474)                                                        \
	LOG_FUNC(475)                                                        \
	LOG_FUNC(476)                                                        \
	LOG_FUNC(477)                                                        \
	LOG_FUNC(478)                                                        \
	LOG_FUNC(479)                                                        \
	LOG_FUNC(480)                                                        \
	LOG_FUNC(481)                                                        \
	LOG_FUNC(482)                                                        \
	LOG_FUNC(483)                                                        \
	LOG_FUNC(484)                                                        \
	LOG_FUNC(485)                                                        \
	LOG_FUNC(486)                                                        \
	LOG_FUNC(487)                                                        \
	LOG_FUNC(488)                                                        \
	LOG_FUNC(489)                                                        \
	LOG_FUNC(490)                                                        \
	LOG_FUNC(491)                                                        \
	LOG_FUNC(492)                                                        \
	LOG_FUNC(493)                                                        \
	LOG_FUNC(494)                                                        \
	LOG_FUNC(495)                                                        \
	LOG_FUNC(496)                                                        \
	LOG_FUNC(497)                                                        \
	LOG_FUNC(498)                                                        \
	LOG_FUNC(499)                                                        \
	LOG_FUNC(500)                                                        \
	LOG_FUNC(501)                                                        \
	LOG_FUNC(502)                                                        \
	LOG_FUNC(503)                                                        \
	LOG_FUNC(504)                                                        \
	LOG_FUNC(505)                                                        \
	LOG_FUNC(506)                                                        \
	LOG_FUNC(507)                                                        \
	LOG_FUNC(508)                                                        \
	LOG_FUNC(509)                                                        \
	LOG_FUNC(510)                                                        \
	LOG_FUNC(511)                                                        \
	LOG_FUNC(512)                                                        \
	LOG_FUNC(513)                                                        \
	LOG_FUNC(514)                                                        \
	LOG_FUNC(515)                                                        \
	LOG_FUNC(516)                                                        \
	LOG_FUNC(517)                                                        \
	LOG_FUNC(518)                                                        \
	LOG_FUNC(519)                                                        \
	LOG_FUNC(520)                                                        \
	LOG_FUNC(521)                                                        \
	LOG_FUNC(522)                                                        \
	LOG_FUNC(523)                                                        \
	LOG_FUNC(524)                                                        \
	LOG_FUNC(525)                                                        \
	LOG_FUNC(526)                                                        \
	LOG_FUNC(527)                                                        \
	LOG_FUNC(528)                                                        \
	LOG_FUNC(529)                                                        \
	LOG_FUNC(530)                                                        \
	LOG_FUNC(531)                                                        \
	LOG_FUNC(532)                                                        \
	LOG_FUNC(533)                                                        \
	LOG_FUNC(534)                                                        \
	LOG_FUNC(535)                                                        \
	LOG_FUNC(536)                                                        \
	LOG_FUNC(537)                                                        \
	LOG_FUNC(538)                                                        \
	LOG_FUNC(539)                                                        \
	LOG_FUNC(540)                                                        \
	LOG_FUNC(541)                                                        \
	LOG_FUNC(542)                                                        \
	LOG_FUNC(543)                                                        \
	LOG_FUNC(544)                                                        \
	LOG_FUNC(545)                                                        \
	LOG_FUNC(546)                                                        \
	LOG_FUNC(547)                                                        \
	LOG_FUNC(548)                                                        \
	LOG_FUNC(549)                                                        \
	LOG_FUNC(550)                                                        \
	LOG_FUNC(551)                                                        \
	LOG_FUNC(552)                                                        \
	LOG_FUNC(553)                                                        \
	LOG_FUNC(554)                                                        \
	LOG_FUNC(555)                                                        \
	LOG_FUNC(556)                                                        \
	LOG_FUNC(557)                                                        \
	LOG_FUNC(558)                                                        \
	LOG_FUNC(559)                                                        \
	LOG_FUNC(560)                                                        \
	LOG_FUNC(561)                                                        \
	LOG_FUNC(562)                                                        \
	LOG_FUNC(563)                                                        \
	LOG_FUNC(564)                                                        \
	LOG_FUNC(565)                                                        \
	LOG_FUNC(566)                                                        \
	LOG_FUNC(567)                                                        \
	LOG_FUNC(568)                                                        \
	LOG_FUNC(569)                                                        \
	LOG_FUNC(570)                                                        \
	LOG_FUNC(571)                                                        \
	LOG_FUNC(572)                                                        \
	LOG_FUNC(573)                                                        \
	LOG_FUNC(574)                                                        \
	LOG_FUNC(575)                                                        \
	LOG_FUNC(576)                                                        \
	LOG_FUNC(577)                                                        \
	LOG_FUNC(578)                                                        \
	LOG_FUNC(579)                                                        \
	LOG_FUNC(580)                                                        \
	LOG_FUNC(581)                                                        \
	LOG_FUNC(582)                                                        \
	LOG_FUNC(583)                                                        \
	LOG_FUNC(584)                                                        \
	LOG_FUNC(585)                                                        \
	LOG_FUNC(586)                                                        \
	LOG_FUNC(587)                                                        \
	LOG_FUNC(588)                                                        \
	LOG_FUNC(589)                                                        \
	LOG_FUNC(590)                                                        \
	LOG_FUNC(591)                                                        \
	LOG_FUNC(592)                                                        \
	LOG_FUNC(593)                                                        \
	LOG_FUNC(594)                                                        \
	LOG_FUNC(595)                                                        \
	LOG_FUNC(596)                                                        \
	LOG_FUNC(597)                                                        \
	LOG_FUNC(598)                                                        \
	LOG_FUNC(599)                                                        \
	static fn_log_func log_funcs[] = {                                   \
		log_func0,	 log_func1,	  log_func2,   log_func3,	log_func4,   \
		log_func5,	 log_func6,	  log_func7,   log_func8,	log_func9,   \
		log_func10,	 log_func11,  log_func12,  log_func13,	log_func14,  \
		log_func15,	 log_func16,  log_func17,  log_func18,	log_func19,  \
		log_func20,	 log_func21,  log_func22,  log_func23,	log_func24,  \
		log_func25,	 log_func26,  log_func27,  log_func28,	log_func29,  \
		log_func30,	 log_func31,  log_func32,  log_func33,	log_func34,  \
		log_func35,	 log_func36,  log_func37,  log_func38,	log_func39,  \
		log_func40,	 log_func41,  log_func42,  log_func43,	log_func44,  \
		log_func45,	 log_func46,  log_func47,  log_func48,	log_func49,  \
		log_func50,	 log_func51,  log_func52,  log_func53,	log_func54,  \
		log_func55,	 log_func56,  log_func57,  log_func58,	log_func59,  \
		log_func60,	 log_func61,  log_func62,  log_func63,	log_func64,  \
		log_func65,	 log_func66,  log_func67,  log_func68,	log_func69,  \
		log_func70,	 log_func71,  log_func72,  log_func73,	log_func74,  \
		log_func75,	 log_func76,  log_func77,  log_func78,	log_func79,  \
		log_func80,	 log_func81,  log_func82,  log_func83,	log_func84,  \
		log_func85,	 log_func86,  log_func87,  log_func88,	log_func89,  \
		log_func90,	 log_func91,  log_func92,  log_func93,	log_func94,  \
		log_func95,	 log_func96,  log_func97,  log_func98,	log_func99,  \
		log_func100, log_func101, log_func102, log_func103, log_func104, \
		log_func105, log_func106, log_func107, log_func108, log_func109, \
		log_func110, log_func111, log_func112, log_func113, log_func114, \
		log_func115, log_func116, log_func117, log_func118, log_func119, \
		log_func120, log_func121, log_func122, log_func123, log_func124, \
		log_func125, log_func126, log_func127, log_func128, log_func129, \
		log_func130, log_func131, log_func132, log_func133, log_func134, \
		log_func135, log_func136, log_func137, log_func138, log_func139, \
		log_func140, log_func141, log_func142, log_func143, log_func144, \
		log_func145, log_func146, log_func147, log_func148, log_func149, \
		log_func150, log_func151, log_func152, log_func153, log_func154, \
		log_func155, log_func156, log_func157, log_func158, log_func159, \
		log_func160, log_func161, log_func162, log_func163, log_func164, \
		log_func165, log_func166, log_func167, log_func168, log_func169, \
		log_func170, log_func171, log_func172, log_func173, log_func174, \
		log_func175, log_func176, log_func177, log_func178, log_func179, \
		log_func180, log_func181, log_func182, log_func183, log_func184, \
		log_func185, log_func186, log_func187, log_func188, log_func189, \
		log_func190, log_func191, log_func192, log_func193, log_func194, \
		log_func195, log_func196, log_func197, log_func198, log_func199, \
		log_func200, log_func201, log_func202, log_func203, log_func204, \
		log_func205, log_func206, log_func207, log_func208, log_func209, \
		log_func210, log_func211, log_func212, log_func213, log_func214, \
		log_func215, log_func216, log_func217, log_func218, log_func219, \
		log_func220, log_func221, log_func222, log_func223, log_func224, \
		log_func225, log_func226, log_func227, log_func228, log_func229, \
		log_func230, log_func231, log_func232, log_func233, log_func234, \
		log_func235, log_func236, log_func237, log_func238, log_func239, \
		log_func240, log_func241, log_func242, log_func243, log_func244, \
		log_func245, log_func246, log_func247, log_func248, log_func249, \
		log_func250, log_func251, log_func252, log_func253, log_func254, \
		log_func255, log_func256, log_func257, log_func258, log_func259, \
		log_func260, log_func261, log_func262, log_func263, log_func264, \
		log_func265, log_func266, log_func267, log_func268, log_func269, \
		log_func270, log_func271, log_func272, log_func273, log_func274, \
		log_func275, log_func276, log_func277, log_func278, log_func279, \
		log_func280, log_func281, log_func282, log_func283, log_func284, \
		log_func285, log_func286, log_func287, log_func288, log_func289, \
		log_func290, log_func291, log_func292, log_func293, log_func294, \
		log_func295, log_func296, log_func297, log_func298, log_func299, \
		log_func300, log_func301, log_func302, log_func303, log_func304, \
		log_func305, log_func306, log_func307, log_func308, log_func309, \
		log_func310, log_func311, log_func312, log_func313, log_func314, \
		log_func315, log_func316, log_func317, log_func318, log_func319, \
		log_func320, log_func321, log_func322, log_func323, log_func324, \
		log_func325, log_func326, log_func327, log_func328, log_func329, \
		log_func330, log_func331, log_func332, log_func333, log_func334, \
		log_func335, log_func336, log_func337, log_func338, log_func339, \
		log_func340, log_func341, log_func342, log_func343, log_func344, \
		log_func345, log_func346, log_func347, log_func348, log_func349, \
		log_func350, log_func351, log_func352, log_func353, log_func354, \
		log_func355, log_func356, log_func357, log_func358, log_func359, \
		log_func360, log_func361, log_func362, log_func363, log_func364, \
		log_func365, log_func366, log_func367, log_func368, log_func369, \
		log_func370, log_func371, log_func372, log_func373, log_func374, \
		log_func375, log_func376, log_func377, log_func378, log_func379, \
		log_func380, log_func381, log_func382, log_func383, log_func384, \
		log_func385, log_func386, log_func387, log_func388, log_func389, \
		log_func390, log_func391, log_func392, log_func393, log_func394, \
		log_func395, log_func396, log_func397, log_func398, log_func399, \
		log_func400, log_func401, log_func402, log_func403, log_func404, \
		log_func405, log_func406, log_func407, log_func408, log_func409, \
		log_func410, log_func411, log_func412, log_func413, log_func414, \
		log_func415, log_func416, log_func417, log_func418, log_func419, \
		log_func420, log_func421, log_func422, log_func423, log_func424, \
		log_func425, log_func426, log_func427, log_func428, log_func429, \
		log_func430, log_func431, log_func432, log_func433, log_func434, \
		log_func435, log_func436, log_func437, log_func438, log_func439, \
		log_func440, log_func441, log_func442, log_func443, log_func444, \
		log_func445, log_func446, log_func447, log_func448, log_func449, \
		log_func450, log_func451, log_func452, log_func453, log_func454, \
		log_func455, log_func456, log_func457, log_func458, log_func459, \
		log_func460, log_func461, log_func462, log_func463, log_func464, \
		log_func465, log_func466, log_func467, log_func468, log_func469, \
		log_func470, log_func471, log_func472, log_func473, log_func474, \
		log_func475, log_func476, log_func477, log_func478, log_func479, \
		log_func480, log_func481, log_func482, log_func483, log_func484, \
		log_func485, log_func486, log_func487, log_func488, log_func489, \
		log_func490, log_func491, log_func492, log_func493, log_func494, \
		log_func495, log_func496, log_func497, log_func498, log_func499, \
		log_func500, log_func501, log_func502, log_func503, log_func504, \
		log_func505, log_func506, log_func507, log_func508, log_func509, \
		log_func510, log_func511, log_func512, log_func513, log_func514, \
		log_func515, log_func516, log_func517, log_func518, log_func519, \
		log_func520, log_func521, log_func522, log_func523, log_func524, \
		log_func525, log_func526, log_func527, log_func528, log_func529, \
		log_func530, log_func531, log_func532, log_func533, log_func534, \
		log_func535, log_func536, log_func537, log_func538, log_func539, \
		log_func540, log_func541, log_func542, log_func543, log_func544, \
		log_func545, log_func546, log_func547, log_func548, log_func549, \
		log_func550, log_func551, log_func552, log_func553, log_func554, \
		log_func555, log_func556, log_func557, log_func558, log_func559, \
		log_func560, log_func561, log_func562, log_func563, log_func564, \
		log_func565, log_func566, log_func567, log_func568, log_func569, \
		log_func570, log_func571, log_func572, log_func573, log_func574, \
		log_func575, log_func576, log_func577, log_func578, log_func579, \
		log_func580, log_func581, log_func582, log_func583, log_func584, \
		log_func585, log_func586, log_func587, log_func588, log_func589, \
		log_func590, log_func591, log_func592, log_func593, log_func594, \
		log_func595, log_func596, log_func597, log_func598, log_func599, \
	};

#endif // !BENCHMARK_LOG_MSG_H_
