use crate::token::Token;

pub struct Ast {
    tokens: Vec<Token>,
}

impl Ast {
    pub fn new() -> Self {
        Self { tokens: Vec::new() }
    }
}
