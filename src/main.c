#include <pebble.h>

#define ARR_SIZE(arr) ( sizeof((arr)) / sizeof((arr[0])) )

// Oblique Strategies © 1975-2001 Brian Eno/Peter Schmidt
char* strategies[] = {
  "Abandon normal instruments",
  "Accept advice",
  "Accretion",
  "A line has two sides",
  "Allow an easement (an easement is the abandonment of a stricture)",
  "Always first steps",
  "Are there sections? Consider transitions",
  "Ask people to work against their better judgement",
  "Ask your body",
  "Assemble some of the elements in a group and treat the group",
  "Balance the consistency principle with the inconsistency principle",
  "Be dirty",
  "Be extravagant",
  "Be less critical more often",
  "Breathe more deeply",
  "Bridges\n-build\n-burn",
  "Cascades",
  "Change instrument roles",
  "Change nothing and continue with immaculate consistency",
  "Children\n-speaking\n-singing",
  "Cluster analysis",
  "Consider different fading systems",
  "Consult other sources\n-promising\n-unpromising",
  "Courage!",
  "Cut a vital connection",
  "Decorate, decorate",
  "Define an area as 'safe' and use it as an anchor",
  "Destroy\n-nothing\n-the most important thing",
  "Discard an axiom",
  "Disciplined self-indulgence",
  "Disconnect from desire",
  "Discover the recipes you are using and abandon them",
  "Distorting time",
  "Do nothing for as long as possible",
  "Don't be afraid of things because they're easy to do",
  "Don't be frightened of cliches",
  "Don't be frightened to display your talents",
  "Don't break the silence",
  "Don't stress one thing more than another",
  "Do something boring",
  "Do the words need changing?",
  "Do we need holes?",
  "Emphasise differences",
  "Emphasise repetitions",
  "Emphasise the flaws",
  "Fill every beat with something",
  "From nothing to more than nothing",
  "Ghost echoes",
  "Give the game away",
  "Give way to your worst impulse",
  "Go outside. Shut the door.",
  "Go slowly all the way round the outside",
  "Go to an extreme, move back to a more comfortable place",
  "Honor thy error as a hidden intention",
  "How would you have done it?",
  "Humanise something free of error",
  "Idiot glee (?)",
  "Imagine the piece as a set of disconnected events",
  "Infinitesimal gradations",
  "Intentions\n-nobility of\n-humility of\n-credibility of",
  "In total darkness, or in a very large room, very quietly",
  "Into the impossible",
  "Is it finished?",
  "Is the intonation correct?",
  "Is there something missing?",
  "It is quite possible (after all)",
  "Just carry on",
  "Listen to the quiet voice",
  "Look at the order in which you do things",
  "Look closely at the most embarrassing details and amplify them",
  "Lost in useless territory",
  "Lowest common denominator",
  "Make a blank valuable by putting it in an exquisite frame",
  "Make an exhaustive list of everything you might do and do the last thing on the list",
  "Make a sudden, destructive unpredictable action; incorporate",
  "Mechanicalise something idiosyncratic",
  "Mute and continue",
  "Not building a wall but making a brick",
  "Once the search is in progress, something will be found",
  "Only a part, not the whole",
  "Only one element of each kind",
  "(Organic) machinery",
  "Overtly resist change",
  "Question the heroic approach",
  "Remember .those quiet evenings",
  "Remove ambiguities and convert to specifics",
  "Remove specifics and convert to ambiguities",
  "Repetition is a form of change",
  "Retrace your steps",
  "Revaluation (a warm feeling)",
  "Reverse",
  "Short circuit (example; a man eating peas with the idea that they will improve his virility shovels them straight into his lap)",
  "Simple subtraction",
  "Simply a matter of work",
  "State the problem in words as clearly as possible",
  "Take a break",
  "Take away the elements in order of apparent non-importance",
  "The inconsistency principle",
  "The most important thing is the thing most easily forgotten",
  "The tape is now the music",
  "Think of the radio",
  "Tidy up",
  "Towards the insignificant",
  "Trust in the you of now",
  "Turn it upside down",
  "Use an old idea",
  "Use an unacceptable colour",
  "Use fewer notes",
  "Use filters",
  "Use 'unqualified' people",
  "Water",
  "What are the sections sections of? Imagine a caterpillar moving",
  "What are you really thinking about just now?",
  "What is the reality of the situation?",
  "What mistakes did you make last time?",
  "What wouldn't you do?",
  "What would your closest friend do?",
  "Work at a different speed",
  "Would anybody want it?",
  "You are an engineer",
  "You can only make one dot at a time",
  "You don't have to be ashamed of using your own ideas",
  ""
};

static Window *window_time;
static TextLayer *time_layer;

static Window *window_strategy;
static TextLayer *text_layer;
static bool showing_time = true;

static void update_time() {
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);
  text_layer_set_text(time_layer, s_buffer);
}

static void update_strategy(){
  Layer *root_window = window_get_root_layer(window_strategy);
  srand(time(0));
  char* text = strategies[rand() % ARR_SIZE(strategies)];
  GRect bounds = layer_get_bounds(root_window);
  text_layer = text_layer_create((GRect) { .origin = { 0, 0}, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_text(text_layer, text);
  GSize textSize = text_layer_get_content_size(text_layer);
  // re-create text_layer, vertically centered
  text_layer = text_layer_create((GRect) { .origin = { 0, (bounds.size.h/2) - (textSize.h/2) }, .size = { bounds.size.w, bounds.size.h } });
  text_layer_set_text(text_layer, text);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_remove_child_layers(root_window);
  layer_add_child(root_window, text_layer_get_layer(text_layer));
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  time_layer = text_layer_create(GRect(0, (bounds.size.h/2) - 28, bounds.size.w, 50));
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_text(time_layer, "00:00");
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(time_layer));
}

static void main_window_unload(Window *window) {
  text_layer_destroy(time_layer);
}

static void tap_handler(AccelAxisType axis, int32_t direction) {
  if (showing_time){
    showing_time = false;
    update_strategy();
    window_stack_push(window_strategy, true);
  }else{
    showing_time = true;
    window_stack_pop_all(false);
    window_stack_push(window_time, true);
    update_time();
  }
}

static void window_load_strategy(Window *window) {
  update_strategy();
}

static void window_unload_strategy(Window *window) {
  text_layer_destroy(text_layer);
}

static void init() {  
  window_time = window_create();
  window_set_window_handlers(window_time, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(window_time, true);
  update_time();
  
  window_strategy = window_create();
  window_set_window_handlers(window_strategy, (WindowHandlers) {
    .load = window_load_strategy,
    .unload = window_unload_strategy,
  });
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  accel_tap_service_subscribe(tap_handler);
}

static void deinit() {
  window_destroy(window_time);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}