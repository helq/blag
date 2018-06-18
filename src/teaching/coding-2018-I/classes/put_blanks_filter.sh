
jq_definitions="$(mktemp /tmp/jq_built_in-script.XXXXXX)"

cat >> "$jq_definitions" <<<'
# Apply f to composite entities recursively, and to atoms
def walk(f):
  . as $in
  | if type == "object" then
      reduce keys_unsorted[] as $key
        ( {}; . + { ($key):  ($in[$key] | walk(f)) } ) | f
  elif type == "array" then map( walk(f) ) | f
  else f
  end;

walk(
  if (type == "object" and (.t == "Link") and (.c[2][0] == "~h")) then
    {t: "Span",
     c: [
       ["",[],[]],
       ([
        {t: "RawInline",
         c: ["latex", "\\uline{"]}
        ]
        +.c[1]+
        [
        {t: "RawInline",
         c: ["latex", "}"]}
        ])
     ]
    }
  else
    .
  end)
'

jq -f "$jq_definitions"
