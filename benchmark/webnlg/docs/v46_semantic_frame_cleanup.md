# V46 semantic frame cleanup

Removed risky alternative frames after reviewing formatted-match=no cases.

Removed blocks: 32

- SENT -> NP VREL NP { :: city
- SENT -> NP VREL NP { :: city
- SENT -> NP cop det ARG _musician_ { :: genre
- SENT -> NP cop det ARG _artist_ { :: genre
- SENT -> NP _performs_ ARG _music_ { :: genre
- SENT -> NP _plays_ ARG _music_ { :: genre
- SENT -> NP cop _associated_ prep NP { :: associated_Musical_Artist
- SENT -> NP cop _associated_ prep NP { :: associated_Band
- SENT -> NP cop _associated_ prep NP { :: associated_Acts
- SENT -> NP _plays_ prep det common_noun ARG { :: associated_Musical_Artist
- SENT -> NP _plays_ prep det common_noun ARG { :: associated_Band
- SENT -> NP _plays_ prep det common_noun ARG { :: associated_Acts
- SENT -> NP _plays_ prep det common_noun ARG { :: associated_Band_associated_Musical_Artist
- SENT -> NP cop det common_noun prep NP { :: associated_Musical_Artist
- SENT -> NP cop det common_noun prep NP { :: associated_Band
- SENT -> NP cop det common_noun prep NP { :: associated_Acts
- SENT -> NP cop _part_word_ prep NP { :: associated_Musical_Artist
- SENT -> NP cop _part_word_ prep NP { :: associated_Band
- SENT -> NP cop _part_word_ prep NP { :: associated_Acts
- SENT -> NP _was_ det common_noun prep det ARG _band_word_ { :: associated_Musical_Artist
- SENT -> NP _was_ det common_noun prep det ARG _band_word_ { :: associated_Band
- SENT -> NP _was_ det common_noun prep det ARG _band_word_ { :: associated_Acts
- SENT -> det common_noun NP cop _associated_ prep det common_noun NP { :: associated_Musical_Artist
- SENT -> det common_noun NP cop _associated_ prep det common_noun NP { :: associated_Band
- SENT -> NP _performed_ prep NP { :: associated_Musical_Artist
- SENT -> NP _performed_ prep NP { :: associated_Band
- SENT -> NP cop det _city_word_ prep NP { :: country
- SENT -> det _leader_word_ prep NP cop NP { :: leader_Title
- SENT -> NP cop det _leader_word_ prep NP { :: leader_Title
- SENT -> NP _was_ ARG { :: office
- SENT -> NP _was_ ARG { :: office_worked_At_worked_As
- SENT -> NP _has_ det _leader_title_word_ prep ARG { :: leader_Title
